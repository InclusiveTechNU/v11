#  Copyright 2020 Northwestern Inclusive Technology Lab
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

load(
    ":base.bzl",
    "get_cc_library_headers",
    "get_cc_library_includes",
    "get_rel_path",
    "get_virtual_library_dirname",
)

# Supported Node Addon Extensions
_cpp_header_extensions = [".h", ".hh", ".hpp", ".hxx", ".h++"]
_cpp_source_extensions = [".cc", ".cpp", ".cxx", ".c++"]
_cpp_extensions = _cpp_header_extensions + _cpp_source_extensions

# Node Addon Build Details
_node_addon_build_file_name = "binding.gyp"
_gyp_exec_script_name = "build.sh"
_node_gyp_bin_path = "node-gyp/bin/node-gyp.js"
_node_gyp_description = "NodeAddonBuild"
_hdr_include_dirname = "_virtual_includes"

def _get_gyp_src_path(dir_path, gyp_dir_path):
    dir_comps = dir_path.split("/")
    gyp_comps = gyp_dir_path.split("/")
    start_index = gyp_comps.index(dir_comps[0])
    if start_index == -1:
        return None
    relative_path_comps = []
    for i in range(len(dir_comps)):
        dir_comp = dir_comps[i]
        if start_index + i >= len(gyp_comps) or gyp_comps[start_index + i] != dir_comp:
            relative_path_comps.append(dir_comp)
    return "/".join(relative_path_comps)

def _gen_addon_build_files(ctx, name):
    # TODO(tommymchugh): Generate debug and release files
    starting_path = "build/Release/"
    src_objects = []
    src_name_start = starting_path + "obj.target/" + name + "/"
    for file in ctx.files.srcs:
        file_name = file.basename
        file_ext = file.extension
        file_name = file_name.replace("." + file_ext, "")
        output_path = src_name_start + file_name + ".o"
        src_objects.append(output_path)
    return src_objects + [
        starting_path + name + ".node",
    ]

def _gen_gyp_build_subs(
        name,
        srcs,
        gyp_dirname,
        deps = [],
        includes = [],
        cflags = [],
        mac_sdks = []):
    # Generate Apple SDK dependencies
    mac_sdks_full = []
    for sdk in mac_sdks:
        mac_sdks_full.append("$(SDKROOT)/System/Library/Frameworks/" + sdk + ".framework")

    # Generate include directories
    default_includes = [
        ".",
        "<!(NODE_PATH=$(which node); echo \"$NODE_PATH\" | sed \"s/bin\\/node/include/\")",
    ]
    include_dirs = default_includes + includes

    # Generate source file paths
    src_paths = []
    for src_file in srcs:
        src_paths.append(_get_gyp_src_path(src_file.path, gyp_dirname))

    # Substitute template entries in binding.gyp file
    return {
        "{{TARGET_NAME}}": name,
        "{{SOURCES}}": str(src_paths),
        "{{DEPENDENCIES}}": str(deps),
        "{{INCLUDE_DIRS}}": str(include_dirs),
        "{{CFLAGS}}": str(cflags),
        "{{MACOS_SDKS}}": str(mac_sdks_full),
    }

def _gen_virtual_includes(ctx):
    virtual_hdrs = []
    declared_hdrs = ctx.files.hdrs
    for declared_hdr in declared_hdrs:
        # Strip header include prefix
        # TODO(tommymchugh): Follow bazel default for stripping
        full_incl_path = declared_hdr.short_path
        strip_prefix = ctx.attr.strip_include_prefix
        if len(strip_prefix) >= 2 and strip_prefix[:2] == "//":
            strip_prefix = strip_prefix[2:]
        if len(strip_prefix) > 0:
            rel_incl_path = full_incl_path.replace(strip_prefix, "")
        else:
            rel_incl_path = full_incl_path

        # Symlink generated virtual header
        virtual_hdr_container = _hdr_include_dirname + "/" + ctx.label.name
        virtual_hdr_path = virtual_hdr_container + rel_incl_path
        virtual_hdr = ctx.actions.declare_file(virtual_hdr_path)
        ctx.actions.symlink(
            output = virtual_hdr,
            target_file = declared_hdr,
        )
        virtual_hdrs.append(virtual_hdr)
    return virtual_hdrs

def _node_native_library_impl(ctx):
    # TODO(tommymchugh): Platform dependent seperator
    seperator = "/"
    gyp_build_file = ctx.actions.declare_file(_node_addon_build_file_name)

    # TODO(tommymchugh): source files which don't have a stripped prefix break
    # Capture dependency headers and include dirs
    deps_hdrs = []
    deps_includes = []
    for dep in ctx.attr.deps:
        deps_hdrs.append(get_cc_library_headers(dep))
        deps_includes.append(get_cc_library_includes(dep))

    # Generate relative include directories
    deps_includes_rel = []
    for dep_includes_comp in deps_includes:
        for dep in dep_includes_comp.to_list():
            rel_path = get_rel_path(dep, gyp_build_file.dirname)
            deps_includes_rel.append(rel_path)

    # Generate and add header include directories
    virtual_include_files = _gen_virtual_includes(ctx)
    virtual_include_path = ["./" + _hdr_include_dirname + "/" + ctx.label.name]
    gyp_includes = ctx.attr.includes + deps_includes_rel + virtual_include_path

    # Generate libraries from linked dependencies
    linked_paths = []
    full_linked_deps = depset([], order = "default")
    external_deps = []
    for dep_lib in ctx.attr.deps:
        cc_info = dep_lib[CcInfo]
        hdrs = cc_info.compilation_context.headers
        for hdr in hdrs.to_list():
            hdr_comps = hdr.path.split("/")
            root_path = hdr_comps[0]
            if root_path == "external":
                external_deps.append(hdr)
        linker_inputs = cc_info.linking_context.linker_inputs.to_list()
        for linker_input in linker_inputs:
            libraries = linker_input.libraries
            for library in libraries:
                dynamic_lib = library.resolved_symlink_dynamic_library
                static_lib = library.static_library
                if static_lib != None:
                    if static_lib.short_path not in linked_paths:
                        full_linked_deps = depset([static_lib], transitive = [full_linked_deps])
                        linked_paths.append(static_lib.short_path)
                elif dynamic_lib != None:
                    if dynamic_lib.short_path not in linked_paths:
                        full_linked_deps = depset([dynamic_lib], transitive = [full_linked_deps])
                        linked_paths.append(dynamic_lib.short_path)

    # Generate virtual libraries from deps
    vlib_dirname = get_virtual_library_dirname()
    linked_deps = []
    link_dep_paths = []
    for dep_lib in full_linked_deps.to_list():
        path_comps = dep_lib.short_path.split("/")
        if path_comps[0] != "..":
            dep_lib_rel_path = vlib_dirname + seperator + dep_lib.short_path
            dep_lib_path = "build/Release/" + dep_lib_rel_path
        else:
            path_comps[0] = "external"
            dep_lib_rel_path = vlib_dirname + seperator + seperator.join(path_comps)
            dep_lib_path = "build/Release/" + dep_lib_rel_path
        dep_lib_file = ctx.actions.declare_file(dep_lib_path)
        ctx.actions.symlink(
            output = dep_lib_file,
            target_file = dep_lib,
        )
        link_dep_paths.append("<(PRODUCT_DIR)/" + dep_lib_rel_path)
        linked_deps.append(dep_lib_file)

    external_paths = []
    for dep_lib in external_deps:
        dep_lib_path = "build/Release/" + vlib_dirname + seperator + dep_lib.path
        dep_lib_file = ctx.actions.declare_file(dep_lib_path)
        ctx.actions.symlink(
            output = dep_lib_file,
            target_file = dep_lib,
        )
        path_comps = dep_lib.path.split("/")
        external_paths.append("./build/Release/" + vlib_dirname + seperator + path_comps[0] + seperator + path_comps[1])
        linked_deps.append(dep_lib_file)
    external_paths_set = depset(external_paths)
    gyp_includes += external_paths_set.to_list()

    # Generate binding.gyp file from build sources
    gyp_build_subs = _gen_gyp_build_subs(
        ctx.label.name,
        ctx.files.srcs,
        gyp_build_file.dirname,
        link_dep_paths,
        gyp_includes,
        ctx.attr.copts,
        ctx.attr.apple_sdks,
    )
    ctx.actions.expand_template(
        output = gyp_build_file,
        template = ctx.file._build_file_template,
        substitutions = gyp_build_subs,
    )

    # Create Source File Symlinks
    src_symlinks = []
    for file in ctx.files.srcs:
        symlink_path = _get_gyp_src_path(file.path, gyp_build_file.dirname)
        file_link = ctx.actions.declare_file(symlink_path)
        ctx.actions.symlink(
            output = file_link,
            target_file = file,
        )
        src_symlinks.append(file_link)

    # Identify Node Gyp Binary File
    node_gyp_bin_file = None
    for file in ctx.files._node_gyp:
        if _node_gyp_bin_path in file.short_path:
            node_gyp_bin_file = file
    if node_gyp_bin_file == None:
        return []

    # Run Node Gyp Build on generated bindings.gyp
    addon_inputs = ([gyp_build_file] +
                    src_symlinks +
                    linked_deps +
                    virtual_include_files)
    for dep in deps_hdrs:
        addon_inputs += dep.to_list()
    addon_output_file_paths = _gen_addon_build_files(ctx, ctx.label.name)
    addon_output_files = []
    for addon_output_file_path in addon_output_file_paths:
        addon_output_file = ctx.actions.declare_file(addon_output_file_path)
        addon_output_files.append(addon_output_file)
    ctx.actions.run(
        executable = node_gyp_bin_file,
        inputs = addon_inputs,
        arguments = ["-C", gyp_build_file.dirname, "configure", "build"],
        mnemonic = _node_gyp_description,
        outputs = addon_output_files,
        use_default_shell_env = True,
    )

    # Create a JS loader file to output
    loader_file = ctx.actions.declare_file(ctx.label.name + ".js")
    ctx.actions.expand_template(
        output = loader_file,
        template = ctx.file._loader_file_template,
        substitutions = {
            "{{MODULE_PATH}}": "build/Release/" + ctx.label.name,
        },
    )
    return [DefaultInfo(
        runfiles = ctx.runfiles(
            files = addon_output_files + [loader_file],
        ),
        files = depset(addon_output_files + [loader_file]),
    )]

node_native_module = rule(
    implementation = _node_native_library_impl,
    attrs = {
        # Public User-Facing Attributes
        "srcs": attr.label_list(allow_files = _cpp_source_extensions),
        "hdrs": attr.label_list(allow_files = _cpp_header_extensions),
        "deps": attr.label_list(),
        "includes": attr.string_list(),
        "copts": attr.string_list(),
        "strip_include_prefix": attr.string(
            default = "",
        ),
        "apple_sdks": attr.string_list(
            default = [],
        ),

        # Private Attributes
        "_build_file_template": attr.label(
            allow_single_file = True,
            default = "//tools/bazel/templates:binding.gyp.tpl",
        ),
        "_loader_file_template": attr.label(
            allow_single_file = True,
            default = "//tools/bazel/templates:loader.js.tpl",
        ),
        "_node_gyp": attr.label(
            default = "@npm//node-gyp",
        ),
    },
)
