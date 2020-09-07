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

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "larkin/environment/system/platform/get_platform.h"

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
