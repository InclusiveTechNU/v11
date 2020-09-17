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

#include "larkin/environment/system/platform/platform_linux.h"

namespace sys {

PlatformLinux::PlatformLinux() {
    native_process_info_ = new utsname;
}

PlatformLinux::~PlatformLinux() {
    delete native_process_info_;
}

Version PlatformLinux::ConvertSringToVersion(const std::string& value) const {
    return {-1,-1,-1};
}

OperatingSystem PlatformLinux::GetOperatingSystem() const {
    return OperatingSystem::kLinux;
}

Version PlatformLinux::GetVersion() const {
    std::string version_txt = std::string(native_process_info_->version);
    return ConvertSringToVersion(version_txt);
}

std::string PlatformLinux::GetPlatformName() const {
    return std::string(native_process_info_->sysname);
}

}  // namespace sys
