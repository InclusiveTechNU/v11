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

namespace sys {
namespace platform {

// Operating system related platforms that Larkin supports.
enum platform {
    MAC,
    WINDOWS,
    LINUX,
    UNKNOWN,
};

// Platform version numbers following a major, minor,
// and patch number system.
struct version {
    int major_version;
    int minor_version;
    int patch_version;
};

// Operating system specific information including
// the operating system type (mac, windows, linux),
// the version of the OS, and whether the system is a mobile
// platform. As mobile devices are currently not supported,
// mobile defaults to false.
struct platform_info {
    const platform type;
    const sys::platform::version version;
    const bool mobile;
};

};  // namespace platform
};  // namespace sys
