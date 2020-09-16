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
#include "larkin/environment/system/platform/platform_mac.h"

namespace sys {

Platform* Platform::Create() {
    return new PlatformMac();
}

PlatformMac::PlatformMac() {
    NSProcessInfo* proc_info = [NSProcessInfo processInfo];
    native_process_info_ = (__bridge_retained void*) proc_info; 
}

PlatformMac::~PlatformMac() {
    delete native_process_info_;
}

OperatingSystem PlatformMac::GetOperatingSystem() const {
    return OperatingSystem::kMac;
}

Version PlatformMac::GetVersion() const {
    NSProcessInfo* proc_info (__bridge NSProcessInfo*) native_process_info_;
    NSOperatingSystemVersion version = [proc_info operatingSystemVersion];
    int major_version = (int) version.majorVersion;
    int minor_version = (int) version.minorVersion;
    int patch_version = (int) version.patchVersion;
    return {major_version, minor_version, patch_version};
}

std::string PlatformMac::GetPlatformName() const {
    return "mac";
}

}  // namespace sys
