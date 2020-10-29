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
#include "absl/container/btree_set.h"
#include "larkin/environment/system/system_base.h"
#include "larkin/environment/system/platform/platform.h"
#include "larkin/environment/system/notifications/notification_manager.h"
#include "larkin/environment/application/application.h"

using sys::NotificationManager;
using sys::Platform;
using app::Application;

namespace sys {

class SystemMac : public SystemBase {
 private:
    void LoadRunningApplications();
    void AddApplicationChangeListener();

 public:
    SystemMac();
    ~SystemMac();

    // Inherited From System Base Class
    // TODO(tommymchugh): Change type to ScreenReader class
    const void* GetRunningScreenReader() const;
    void StartApplicationNamed(const std::string& name) const;
    void StartApplicationAtPath(const std::string& path) const;
    void HideOtherApplications() const;
};

}  // namespace sys
