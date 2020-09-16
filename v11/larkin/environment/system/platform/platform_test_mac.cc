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

#include <string>
#include "googletest/include/gtest/gtest.h"
#include "larkin/environment/system/platform/platform.h"
#include "larkin/environment/system/platform/platform_mac.h"

using sys::Platform;
using sys::PlatformMac;
using sys::Version;
using sys::OperatingSystem;

// Tests that on linux devices the platform OS type is linux
TEST(V11LarkinSysPlatformTest, PlatformOperatingSystemIsMac) {
    PlatformMac platform_mac = PlatformMac();
    Platform* platform = &platform_mac;
    EXPECT_EQ(platform->GetOperatingSystem(), OperatingSystem::kMac);
}
