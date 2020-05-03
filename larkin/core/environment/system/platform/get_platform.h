/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "environment/system/platform/platform_info.h"

namespace sys {
namespace platform {
namespace implementation {

const version get_platform_version();
const platform get_platform();

};  // namespace implementation
};  // namespace platform
};  // namespace sys
