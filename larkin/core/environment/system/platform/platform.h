/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
