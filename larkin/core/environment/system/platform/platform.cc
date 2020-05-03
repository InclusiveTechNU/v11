/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "environment/system/platform/platform.h"
#include "environment/system/platform/get_platform.h"

namespace sys {
namespace platform {

const version get_platform_version() {
    return implementation::get_platform_version();
}

const platform get_platform() {
    return implementation::get_platform();
}

const platform_info get_platform_info() {
    return {get_platform(), get_platform_version(), false};
}

};  // namespace platform
};  // namespace sys
