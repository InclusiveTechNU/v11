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

#include "core/system/system_instance.h"
#include "utils/definitions.h"
#if defined(OS_WINDOWS)
    #include "core/system/system_windows.h"
#elif defined(OS_APPLE)
    #include "core/system/system_mac.h"
#elif defined(OS_LINUX)
    #include "core/system/system_linux.h"
#else
    #error "Unknown Operating System Compilation Target"
#endif

namespace sys {

SystemInstance* SystemInstance::instance_ = nullptr;

SystemInstance::SystemInstance() {
    #if defined(OS_WINDOWS)
        system_ = SystemWindows::GetInstance();
    #elif defined(OS_APPLE)
        system_ = SystemMac::GetInstance();
    #elif defined(OS_LINUX)
        system_ = SystemLinux::GetInstance();
    #else
        #error "Unknown Operating System Compilation Target"
    #endif
}

System* SystemInstance::GetInstance() {
    if (!instance_) {
        instance_ = new SystemInstance;
    }
    return instance_->system_;
}

SystemInstance::~SystemInstance() {
    delete system_;
}

}  // namespace sys
