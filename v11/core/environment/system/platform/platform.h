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

#include <string>
#include "core/environment/system/platform/platform_info.h"

namespace sys {

// The Abstract Base Class for a system platform. Contains standard
// details about the version, operating system, and platform specs for
// the platform that the resulting library is being run on.
class Platform {
 public:
    virtual ~Platform() {}

    // Returns the operating system type out of MacOS, Windows, Linux, and
    // unknown systems. All Linux distribution are under the linux type,
    // but specific distro type is avaialble through GetPlatformName().
    virtual OperatingSystem GetOperatingSystem() const = 0;

    // Returns the platform's operating system version as a set of unsigned
    // 16-bit integers representing Major, Minor, and Patch code stored in a
    // version struct.
    virtual Version GetVersion() const = 0;

    // Returns the full platform name for the operating system. This usually
    // remains the same on MacOS and Windows, but will change on different
    // Linux distribution types.
    virtual std::string GetPlatformName() const = 0;

    // Returns the platform's operating system version as a string in the
    // "major.minor.patch string" code format.
    std::string GetVersionAsString() const;

    // Returns a boolean variable representing whether the platform being
    // run is considered a mobile device, i.e a tablet/phone/watch.
    bool IsMobile() const;
};

}  // namespace sys
