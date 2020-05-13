/*
 * Copyright 2020 Northwestern Inclusive Technology Lab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "utils/definitions.h"
#include "environment/system/platform/platform_info.h"

namespace sys {
namespace platform {

// Returns a version struct with the major, minor, and patch
// version of the current operating system environment.
const version get_platform_version();

// Returns the platform type of the current operating system
// environment.
const platform get_platform();

// Returns a platform info object with the type and version of the
// platform. Also includes a boolean that currently defaults to false
// identifying with the platform is mobile.
const platform_info get_platform_info();

};  // namespace platform
};  // namespace sys
