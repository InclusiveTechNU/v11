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

#include "larkin/environment/system/platform/platform_mock.h"

namespace sys {

Platform* Platform::Create() {
    return new MockPlatform();
}

MockPlatform::MockPlatform() {
    mock_platform_name_ = kMockPlatformName;
    mock_version_ = kMockVersion;
    mock_os_ = kMockPlatformOS;
}

OperatingSystem MockPlatform::GetOperatingSystem() const {
    return mock_os_;
}

Version MockPlatform::GetVersion() const {
    return mock_version_;
}

std::string MockPlatform::GetPlatformName() const {
    return mock_platform_name_;
}

void MockPlatform::SetPlatformName(const std::string& platform_name) {
    mock_platform_name_ = platform_name;
}

void MockPlatform::SetVersion(const Version& version) {
    mock_version_ = version;
}

void MockPlatform::SetOperatingSystem(const OperatingSystem& os) {
    mock_os_ = os;
}

}  // namespace sys
