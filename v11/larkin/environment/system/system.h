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
#include "larkin/environment/system/platform/platform.h"
#include "larkin/environment/system/notifications/notification_manager.h"
#include "larkin/environment/application/application.h"

using sys::NotificationManager;
using sys::Platform;
using app::Application;

namespace sys {

// Simple shortcut for stored collections of applications
typedef absl::btree_set<Application*> ApplicationSet;

// A container class that holds major system event listener managers, platform
// information, and updateable application data.
class System {
 public:
    virtual ~System();

    // Returns a read-only pointer to a Platform object that contains
    // information about the native system platform.
    virtual const Platform* GetPlatform() const = 0;

    // Returns a read-only pointer to a pre-allocated notification manager
    // to attach callbacks for system level notification events.
    virtual NotificationManager* const GetNotificationManager() const = 0;

    // Returns a set container of current applications. The container updates
    // as applications are launched and terminated on the system.
    virtual const ApplicationSet* GetRunningApplications() const = 0;

    // TODO(tommymchugh): Change type to ScreenReader class
    // Returns a read-only pointer to the current active screen reader
    // application that is controlling the system.
    virtual const void* GetRunningScreenReader() const = 0;

    // Returns a boolean value representing whether there is a screen reader
    // software active on the native system.
    bool IsScreenReaderRunning() const;

    // Given a bundle ID, the method returns whether a certain application with
    // the gie bundle ID is currently running on the system.
    bool IsApplicationRunning(const std::string& bundle_id) const;

    // TODO(tommymchugh): Create launch options for applications
    // Given an Application name, will search for and try to start an
    // application on the system with the given name.
    virtual void StartApplicationNamed(const std::string& name) const = 0;

    // Will start an application on the native system located at a given path.
    virtual void StartApplicationAtPath(const std::string& path) const = 0;

    // Will hide all applications on the native system besides the caller.
    virtual void HideOtherApplications() const = 0;
};

}  // namespace sys
