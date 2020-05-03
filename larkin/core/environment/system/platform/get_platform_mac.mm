/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "environment/system/platform/get_platform.h"

namespace sys {
namespace platform {
namespace implementation {

const sys::platform::version get_platform_version() {
    NSOperatingSystemVersion current_version = [[NSProcessInfo processInfo] operatingSystemVersion];
    int major_version = (int) current_version.majorVersion;
    int minor_version = (int) current_version.minorVersion;
    int patch_version = (int) current_version.patchVersion;

    return {major_version, minor_version, patch_version};
}

const sys::platform::platform get_platform() {
    return sys::platform::mac;
}

};  // namespace implementation
};  // namespace platform
};  // namespace sys
