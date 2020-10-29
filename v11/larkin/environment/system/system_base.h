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
#include "larkin/environment/system/system.h"
#include "larkin/environment/system/platform/platform.h"
#include "larkin/environment/system/notifications/notification_manager.h"
#include "larkin/environment/application/application.h"

using sys::NotificationManager;
using sys::Platform;
using app::Application;

namespace sys {

class SystemBase : public System {
 private:
    void FreeRunningApplications();

 protected:
    SystemBase();
    Platform* platform_ = nullptr;
    NotificationManager* notification_manager_ = nullptr;
    absl::btree_set<Application*>* runnings_apps_ = nullptr;

 public:
    virtual ~SystemBase();

    // Inherited From System Abstract Base Class
    const Platform* GetPlatform() const;
    NotificationManager* const GetNotificationManager() const;
    const absl::btree_set<Application*>* GetRunningApplications() const;
    // TODO(tommymchugh): Change type to ScreenReader class
    virtual const void* GetRunningScreenReader() const = 0;
    virtual void StartApplicationNamed(const std::string& name) const = 0;
    virtual void StartApplicationAtPath(const std::string& path) const = 0;
    virtual void HideOtherApplications() const = 0;
};

}  // namespace sys
