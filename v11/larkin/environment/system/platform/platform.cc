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

#include "larkin/environment/system/platform/platform.h"
#include "absl/strings/str_format.h"

namespace sys {

OperatingSystem Platform::GetOperatingSystem() const {
    return OperatingSystem::kUnknown;
}

Version Platform::GetVersion() const {
    return {0, 0, 0};
}

std::string Platform::GetVersionAsString() const {
    Version version = GetVersion();
    return absl::StrFormat("%d.%d.%d",
                           version.major_version,
                           version.minor_version,
                           version.patch_version);
}

std::string Platform::GetPlatformName() const {
    return "unknown";
}

bool Platform::IsMobile() const {
    // TODO(tommymchugh): Look into Android support for mobile devices.
    // Mobile devices are currently not supported so defaulting to false.
    return false;
}

}  // namespace sys
