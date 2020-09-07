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

workspace(
    name = "itl",
    managed_directories = {"@npm": ["node_modules"]},
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# Install C++ Build Rules
http_archive(
    name = "rules_cc",
    sha256 = "faa25a149f46077e7eca2637744f494e53a29fe3814bfe240a2ce37115f6e04d",
    strip_prefix = "rules_cc-ea5c5422a6b9e79e6432de3b2b29bbd84eb41081",
    url = "https://github.com/bazelbuild/rules_cc/archive/ea5c5422a6b9e79e6432de3b2b29bbd84eb41081.zip",
)

# Install Node.JS Dependencies for Bazel
http_archive(
    name = "build_bazel_rules_nodejs",
    sha256 = "0f2de53628e848c1691e5729b515022f5a77369c76a09fbe55611e12731c90e3",
    urls = ["https://github.com/bazelbuild/rules_nodejs/releases/download/2.0.1/rules_nodejs-2.0.1.tar.gz"],
)
load("@build_bazel_rules_nodejs//:index.bzl", "node_repositories")
node_repositories(package_json = ["//third_party/node:package.json"])

# Setup Bazel-Managed Dependencies
load("@build_bazel_rules_nodejs//:index.bzl", "yarn_install")
yarn_install(
    name = "npm",
    package_json = "//third_party/node:package.json",
    yarn_lock = "//third_party/node:yarn.lock",
)

# Install Python and Pip Build Rules
http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.2/rules_python-0.0.2.tar.gz",
    strip_prefix = "rules_python-0.0.2",
    sha256 = "b5668cde8bb6e3515057ef465a35ad712214962f0b3a314e551204266c7be90c",
)
load("@rules_python//python:pip.bzl", "pip_repositories", "pip3_import")
pip_repositories()

# Add Pip dependencies from third_party
pip3_import(
   name = "pip",
   requirements = "//third_party/pip:requirements.txt",
)
load("@pip//:requirements.bzl", "pip_install")
pip_install()

# Setup Protobuf library build rules
http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

# Install Multilanguage Protobuf Support
git_repository(
    name = "rules_proto_ext",
    branch = "master",
    init_submodules = True,
    remote = "https://github.com/stackb/rules_proto.git"
)

# Install Python Protobuf Support
load("@rules_proto_ext//python:deps.bzl", "python_proto_library")
python_proto_library()
load("@io_bazel_rules_python//python:pip.bzl", "pip_import")
pip_import(
    name = "protobuf_py_deps",
    requirements = "@rules_proto_ext//python/requirements:protobuf.txt",
)
load("@protobuf_py_deps//:requirements.bzl", protobuf_pip_install = "pip_install")
protobuf_pip_install()
