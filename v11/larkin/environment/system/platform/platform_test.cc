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
#include "larkin/environment/system/platform/platform_mock.h"

using sys::Platform;
using sys::MockPlatform;
using sys::Version;

// TODO(tommymchugh): Remove this once mobile platforms are supported.
// Tests that Platform will return false to IsMobile until supported.
TEST(V11LarkinSysPlatformTest, MobileUnsupported) {
    MockPlatform mock_platform = MockPlatform();
    Platform* platform = &mock_platform;
    EXPECT_FALSE(platform->IsMobile());
}

// Tests that Platform String Version is equal to Version values
TEST(V11LarkinSysPlatformTest, Platform) {
    MockPlatform mock_platform = MockPlatform();
    Platform* platform = &mock_platform;
    Version platform_version = platform->GetVersion();
    int* major_version = &(platform_version.major_version);
    int* minor_version = &(platform_version.minor_version);
    int* patch_version = &(platform_version.patch_version);

    std::string expected_val = std::to_string(*major_version) + "." +
                               std::to_string(*minor_version) + "." +
                               std::to_string(*patch_version);
    EXPECT_EQ(platform->GetVersionAsString(), expected_val);

    mock_platform.SetVersion({60, 50, 40});
    platform_version = platform->GetVersion();
    EXPECT_EQ(platform->GetVersionAsString(), "60.50.40");
    EXPECT_NE(platform->GetVersionAsString(), expected_val);
}