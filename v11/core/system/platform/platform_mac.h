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
#include "core/system/platform/platform_info.h"
#include "core/system/platform/platform.h"

namespace sys {

// Platform class implementation for Mac specific environments
class PlatformMac : public Platform {
    // Class owned native process spec
    void* native_process_info_ = nullptr;

 public:
    PlatformMac();
    ~PlatformMac();

    // Inherited methods from Platform class
    OperatingSystem GetOperatingSystem() const;
    Version GetVersion() const;
    std::string GetPlatformName() const;
};

}  // namespace sys
