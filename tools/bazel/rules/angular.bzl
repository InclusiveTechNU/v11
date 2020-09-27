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

"""Drop in replacements for deprecated Angular ABC build tooling."""

load("@npm//@bazel/typescript:index.bzl", "ts_library")

def ng_ts_library(**kwargs):
    ts_library(
        compiler = "//config/typescript:tsc_wrapped_with_angular",
        supports_workers = True,
        use_angular_plugin = True,
        **kwargs
    )
