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

_virtual_library_dirname = "_virtual_libraries"

def get_virtual_library_dirname():
    return _virtual_library_dirname

def get_cc_library_headers(cc_lib):
    return cc_lib[CcInfo].compilation_context.headers

def get_cc_library_linked_libs(cc_lib):
    linked_libs = []
    inputs = cc_lib[CcInfo].linking_context.linker_inputs.to_list()
    for input in inputs:
        libs = input.libraries
        for lib in libs:
            dyn_lib = lib.resolved_symlink_dynamic_library
            if dyn_lib != None:
                linked_libs.append(dyn_lib)
    return linked_libs

def get_cc_library_includes(cc_lib):
    return cc_lib[CcInfo].compilation_context.includes

def get_common_prefix(path_a, path_b):
    common_path = ""
    for i in range(len(path_a)):
        if i < len(path_b) and path_a[i] == path_b[i]:
            common_path += path_a[i]
        else:
            break
    return common_path

def get_rel_path(path, start_path):
    # Define platform dependent directory seperators
    seperator = "/"
    subtract_dir_sign = ".."
    start_dir_sign = "."

    # Remove shared prefix from path
    shared_prefix = get_common_prefix(path, start_path)
    path = path.replace(shared_prefix, "")
    if path[0] == seperator:
        path = path[1:]

    # Add proper subdirectory seps to path
    start_path = start_path.replace(shared_prefix, "")
    start_path_comps = start_path.split(seperator)
    if len(start_path_comps) == 0 or start_path_comps == [""]:
        path = start_dir_sign + seperator + path
    else:
        for _ in range(len(start_path_comps)):
            path = subtract_dir_sign + seperator + path
    return path
