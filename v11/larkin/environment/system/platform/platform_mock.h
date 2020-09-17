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
#include "larkin/environment/system/platform/platform_info.h"
#include "larkin/environment/system/platform/platform.h"

namespace sys {

// Testing constants for Platform class
const std::string kMockPlatformName = "mock";
const OperatingSystem kMockPlatformOS = OperatingSystem::kUnknown;
const Version kMockVersion = {1, 1, 1};

// Platform class implementation for testing platform features
class MockPlatform : public Platform {
    std::string mock_platform_name_;
    Version mock_version_;
    OperatingSystem mock_os_;
 public:
    MockPlatform();

    // Inherited methods from Platform class
    OperatingSystem GetOperatingSystem() const;
    Version GetVersion() const;
    std::string GetPlatformName() const;

    void SetPlatformName(const std::string& platform_name);
    void SetVersion(const Version& version);
    void SetOperatingSystem(const OperatingSystem& os);
};

}  // namespace sys