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

load("@rules_cc//cc:defs.bzl", "cc_library", "objc_library")

def cross_cc_library(
        name,
        hdrs = [],
        srcs = [],
        macos_hdrs = [],
        linux_hdrs = [],
        windows_hdrs = [],
        macos_srcs = [],
        linux_srcs = [],
        windows_srcs = [],
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

    # Define main wrapper library
    cc_library(
        name = name,
        deps = select({
            "//tools/bazel/platforms:linux": [
                ":" + name + "__foundation__",
            ],
            "//tools/bazel/platforms:macos": [
                ":" + name + "__foundation_objc__",
            ],
            "//tools/bazel/platforms:windows": [
                ":" + name + "__foundation__",
            ],
            "//conditions:default": [],
        }),
        visibility = visibility,
        strip_include_prefix = strip_include_prefix,
    )

    # Define MacOS support Objective-C library
    objc_library(
        name = name + "__foundation_objc__",
        srcs = macos_srcs,
        deps = [
            ":" + name + "__foundation__",
        ],
        alwayslink = True,
        sdk_frameworks = [
            "Foundation",
            "AppKit",
        ],
        visibility = ["//visibility:private"],
    )

    # Define foundation components C++ library
    cc_library(
        name = name + "__foundation__",
        hdrs = hdrs + select({
            "//tools/bazel/platforms:linux": linux_hdrs,
            "//tools/bazel/platforms:windows": windows_hdrs,
            "//tools/bazel/platforms:macos": macos_hdrs,
            "//conditions:default": [],
        }),
        srcs = srcs + select({
            "//tools/bazel/platforms:linux": linux_srcs,
            "//tools/bazel/platforms:windows": windows_srcs,
            "//conditions:default": [],
        }),
        deps = deps,
        strip_include_prefix = strip_include_prefix,
        copts = select({
            "//tools/bazel/platforms:macos": [
                "-stdlib=libc++",
                "-ObjC++",
            ],
            "//conditions:default": [],
        }),
        alwayslink = True,
        visibility = ["//visibility:private"],
    )
