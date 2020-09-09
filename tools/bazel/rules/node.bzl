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

load(":base.bzl", "get_cc_library_headers",
                  "get_cc_library_includes",
                  "get_rel_path")

# Supported Node Addon Extensions
_cpp_header_extensions = [".h", ".hh", ".hpp", ".hxx", ".h++"]
_cpp_source_extensions = [".cc", ".cpp", ".cxx", ".c++"]
_cpp_extensions = _cpp_header_extensions + _cpp_source_extensions

# Node Addon Build Details
_node_addon_build_file_name = "binding.gyp"
_gyp_exec_script_name = "build.sh"
_node_gyp_bin_path = "node-gyp/bin/node-gyp.js"
_node_gyp_description = "NodeAddonBuild"

def _get_gyp_src_path(dir_path, gyp_dir_path):
    dir_comps = dir_path.split("/")
    gyp_comps = gyp_dir_path.split("/")
    start_index = gyp_comps.index(dir_comps[0])
    if start_index == -1:
        return None
    relative_path_comps = []
    for i in range(len(dir_comps)):
        dir_comp = dir_comps[i]
        if start_index+i >= len(gyp_comps) or gyp_comps[start_index+i] != dir_comp:
            relative_path_comps.append(dir_comp)
    return '/'.join(relative_path_comps)

def _gen_addon_bin_path(name):
    return "build/" + name + "/Release/" + name

def _gen_gyp_build_subs(name,
                        srcs,
                        gyp_dirname,
                        deps = [],
                        includes = [],
                        cflags = []):
    # Generate include directories
    include_dirs = ["."] + includes

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
        "{{CFLAGS}}": str(cflags)
    }

def _node_native_library_impl(ctx):
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

    # Generate binding.gyp file from build sources
    gyp_build_subs = _gen_gyp_build_subs(ctx.label.name,
                                         ctx.files.srcs,
                                         gyp_build_file.dirname,
                                         [],
                                         ctx.attr.includes + deps_includes_rel,   
                                         ctx.attr.copts)
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
    addon_inputs = [gyp_build_file] + src_symlinks
    for dep in deps_hdrs:
        addon_inputs += dep.to_list()
    addon_output_bin_path = _gen_addon_bin_path(ctx.label.name)
    addon_output_bin = ctx.actions.declare_file(addon_output_bin_path)
    ctx.actions.run(
        executable = node_gyp_bin_file,
        inputs = addon_inputs,
        arguments = ["-C", gyp_build_file.dirname, "configure", "build"],
        mnemonic = _node_gyp_description,
        outputs = [addon_output_bin],
        use_default_shell_env = True,
    )
    
    return [DefaultInfo(files = depset([
        addon_output_bin
    ]))]

node_native_module = rule(
    implementation = _node_native_library_impl,
    attrs = {
        # Public User-Facing Attributes
        "srcs": attr.label_list(allow_files = _cpp_extensions),
        "deps": attr.label_list(),
        "includes": attr.string_list(),
        "copts": attr.string_list(),
        "strip_include_prefix": attr.string(),

        # Private Attributes
        "_build_file_template": attr.label(
            allow_single_file = True,
            default = "//tools/bazel/templates:binding.gyp.tpl",
        ),
        "_node_gyp": attr.label(
            default = "@npm//node-gyp",
        )
    }
)
