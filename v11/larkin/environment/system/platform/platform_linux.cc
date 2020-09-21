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

#include <fstream>
#include "larkin/environment/system/platform/platform_linux.h"
#include "larkin/environment/system/platform/platform_utils.h"

namespace sys {

PlatformLinux::PlatformLinux() {
    // TODO(tommymchugh): Confirmed working on ubuntu try on other distros
    std::string release_line;
    std::ifstream release_file(kReleaseFilePath);
    bool have_name = false;
    bool have_version = false;
    if (release_file.is_open()) {
        while(getline(release_file, release_line) &&
                      (!have_name || !have_version)) {
            if (release_line.size() > kReleaseName.size() &&
                release_line.substr(0, kReleaseName.size()) == kReleaseName) {
                name_ = release_line.substr(kReleaseName.size() + 2);
                name_.pop_back();
                have_name = true;
            } else if (release_line.size() > kReleaseVersion.size() &&
                       release_line.substr(0, kReleaseVersion.size())
                          == kReleaseVersion) {
                std::size_t ver_size = kReleaseVersion.size();
                std::string version_str = release_line.substr(ver_size + 2);
                version_str.pop_back();
                // Turn string representation into Version
                version_ = PlatformUtils::StringToVersion(version_str);
                have_version = true;
            } 
        }
        release_file.close();
    }
}

OperatingSystem PlatformLinux::GetOperatingSystem() const {
    return OperatingSystem::kLinux;
}

Version PlatformLinux::GetVersion() const {
    return version_;
}

std::string PlatformLinux::GetPlatformName() const {
    return name_;
}

}  // namespace sys
