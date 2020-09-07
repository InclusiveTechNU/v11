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

"""Bazel build helper macros for compiling Obj-C and Obj-C++ projects.

These macros enable rapid development of Objective-C/C++ projects for Bazel.
Specifically, these macros enable cohesion between Non-MacOS libraries and
MacOS libaries that depend on Objective-C native code.
"""

load("@rules_cc//cc:defs.bzl", "cc_library")

def cc_objc_library(name,
                    hdrs = [],
                    srcs = [],
                    deps = [],
                    visibility = ["//visibility:private"],
                    strip_include_prefix = None):
    """Macro for creating a platform-independent C++ & Obj-C library.
    
    Creates a build rule given a name that will either be of cc_library or of
    objc_library type. cc_library type will be generated for Linux & Windows
    platforms, while an objc_library will be generated for MacOS build targets.
    This rule should be used for a library that will work across all
    platforms, but will include Objc-specific code for MacOS.
    
    Args:
        name: The name of the generated build rule.
        hdrs: Build rule header files.
        srcs: Build rule source files.
        deps: Dependencies of the build rule.
        strip_include_prefix: A prefix to be stripped on cc_library builds.
    
    Returns:
        A build rule of either cc_library type or objc_library type depending
        on the platform build target.
    """
    cc_library(
        name = name,
        hdrs = hdrs,
        srcs = srcs,
        deps = deps,
        visibility = visibility,
        strip_include_prefix = strip_include_prefix,
    )
