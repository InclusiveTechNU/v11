/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace sys {
namespace platform {

// Operating system related platforms that Larkin supports.
enum platform {
    mac,
    windows,
    linux,
    unknown
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
    const version version;
    const bool mobile;
};

};  // namespace platform
};  // namespace sys
