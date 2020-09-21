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
#include "larkin/environment/system/platform/platform_utils.h"
#include "larkin/environment/system/platform/platform_info.h"

using sys::PlatformUtils;
using sys::Version;

// Tests that PlatformUtils::StringToVersion converts to Version when given a
// standard version input
TEST(V11LarkinSysPlatformUtilsTest, StringToVersionStandard) {
    const std::string test_ver_one = "20.04.1";
    Version conv_ver = PlatformUtils::StringToVersion(test_ver_one);
    EXPECT_EQ(conv_ver.major_version, 20);
    EXPECT_EQ(conv_ver.minor_version, 4);
    EXPECT_EQ(conv_ver.patch_version, 1);

    const std::string test_ver_two = "15.1";
    conv_ver = PlatformUtils::StringToVersion(test_ver_two);
    EXPECT_EQ(conv_ver.major_version, 15);
    EXPECT_EQ(conv_ver.minor_version, 1);
    EXPECT_EQ(conv_ver.patch_version, 0);

    const std::string test_ver_three = "02";
    conv_ver = PlatformUtils::StringToVersion(test_ver_three);
    EXPECT_EQ(conv_ver.major_version, 2);
    EXPECT_EQ(conv_ver.minor_version, 0);
    EXPECT_EQ(conv_ver.patch_version, 0);

    const std::string test_ver_four = "0.0.01";
    conv_ver = PlatformUtils::StringToVersion(test_ver_four);
    EXPECT_EQ(conv_ver.major_version, 0);
    EXPECT_EQ(conv_ver.minor_version, 0);
    EXPECT_EQ(conv_ver.patch_version, 1);

    const std::string test_ver_five = "0.2.0";
    conv_ver = PlatformUtils::StringToVersion(test_ver_five);
    EXPECT_EQ(conv_ver.major_version, 0);
    EXPECT_EQ(conv_ver.minor_version, 2);
    EXPECT_EQ(conv_ver.patch_version, 0);
}

// Tests that PlatformUtils::StringToVersion works with a range of strings
// that may include some alphanumeric characters.
TEST(V11LarkinSysPlatformUtilsTest, StringToVersionSomeAlphaText) {
    const std::string test_ver_one = "20.04.1 LTS (Focal Fossa)";
    Version conv_ver = PlatformUtils::StringToVersion(test_ver_one);
    EXPECT_EQ(conv_ver.major_version, 20);
    EXPECT_EQ(conv_ver.minor_version, 4);
    EXPECT_EQ(conv_ver.patch_version, 1);

    const std::string test_ver_four = "53 . 22 . 15";
    conv_ver = PlatformUtils::StringToVersion(test_ver_four);
    EXPECT_EQ(conv_ver.major_version, 53);
    EXPECT_EQ(conv_ver.minor_version, 22);
    EXPECT_EQ(conv_ver.patch_version, 15);

    const std::string test_ver_six = "13 . 67 . 2 more sample text";
    conv_ver = PlatformUtils::StringToVersion(test_ver_six);
    EXPECT_EQ(conv_ver.major_version, 13);
    EXPECT_EQ(conv_ver.minor_version, 67);
    EXPECT_EQ(conv_ver.patch_version, 2);
}

TEST(V11LarkinSysPlatformUtilsTest, StringToVersionBadStart) {
    const std::string test_ver_two = "Testing 02.10.06";
    Version conv_ver = PlatformUtils::StringToVersion(test_ver_two);
    EXPECT_NE(conv_ver.major_version, 2);
    EXPECT_EQ(conv_ver.minor_version, 10);
    EXPECT_EQ(conv_ver.patch_version, 6);

    const std::string test_ver_three = "some 3.14.05 pie";
    conv_ver = PlatformUtils::StringToVersion(test_ver_three);
    EXPECT_NE(conv_ver.major_version, 3);
    EXPECT_EQ(conv_ver.minor_version, 14);
    EXPECT_EQ(conv_ver.patch_version, 5);

    const std::string test_ver_five = "sample text here 22 . 13 . 08";
    conv_ver = PlatformUtils::StringToVersion(test_ver_five);
    EXPECT_NE(conv_ver.major_version, 22);
    EXPECT_EQ(conv_ver.minor_version, 13);
    EXPECT_EQ(conv_ver.patch_version, 8);
}
