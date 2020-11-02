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
#include "core/system/system.h"
#include "core/system/platform/platform.h"
#include "core/system/notifications/system_notification_manager.h"
#include "core/application/application.h"

using sys::SystemNotificationManager;
using sys::Platform;
using app::Application;

namespace sys {

// Base class implementation of System. Defines the structure and
// implementation for the non-native specific details of the System class.
class SystemBase : public System {
 private:
    // Deallocates all Application pointers from memory stored in the
    // running applications set. Usually called on class destruction.
    void FreeRunningApplications();

 protected:
    // Native system platform information.
    Platform* platform_ = nullptr;

    // A system-level notification manager.
    SystemNotificationManager* notification_manager_ = nullptr;

    // A container for active running applications to be stored.
    absl::btree_set<Application*>* running_apps_ = nullptr;

    SystemBase();

    // Initially called on class construction, will fill the running
    // applications set with the current active and running applications.
    virtual void LoadRunningApplications() = 0;

    // Adds listeners to the system notification manager for when applications
    // are launched are terminated. When the callbacks for the respective
    // notifications are triggered, the result updates the running applications
    // set container.
    void AddApplicationChangeListener();

 public:
    virtual ~SystemBase();

    // Inherited From System Abstract Base Class
    const Platform* GetPlatform() const;
    SystemNotificationManager* const GetNotificationManager() const;
    const absl::btree_set<Application*>* GetRunningApplications() const;
    virtual const void* GetRunningScreenReader() const = 0;
    virtual void StartApplicationNamed(const std::string& name) const = 0;
    virtual void StartApplicationAtPath(const std::string& path) const = 0;
    virtual void HideOtherApplications() const = 0;
};

}  // namespace sys
