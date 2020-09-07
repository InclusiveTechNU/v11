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

#include <functional>
#include "utils/error.h"
#include "larkin/environment/system/notifications/listener.h"
#include "larkin/environment/system/notifications/notification.h"
#include "larkin/environment/system/notifications/manager_type.h"

using utils::error;

namespace sys {
namespace notifications {

// Provides pointer to native notification manager
// that has transferred ownership to the notification
// manager bridge.
typedef void* native_manager;

class NotificationManagerBridge {
 private:
    // The owned native notification manager pointer
    native_manager notification_manager = nullptr;

    // Whether a notification manager is a system wide
    // or custom manager for specific notifications
    manager_type nm_type;

    // Whether a observer for all notifications has been added to
    // the native notification manager
    bool registered_global_observer = false;

    // A constructor for the bridge that is only accessible from
    // NotificationManagerBridge::create_bridge
    NotificationManagerBridge(native_manager manager, manager_type type);

 public:
    // Transfers the ownership of the native notification bridge
    // back to the system managing it
    ~NotificationManagerBridge();

    // Allocate the memory for a native notification manager and transfer
    // ownership of the manager to the caller
    static NotificationManagerBridge* create_bridge(const manager_type& type);

    // Adds a callback function to every notification identified by the
    // native notification manager that distributes the notifications
    // to any event listeners
    error register_global_observer(const global_observer observer);

    // Removes the global distribution callback function for every notification
    // from the native notification manager
    // ! Blocked until a better way to natively remove observers is implemented
    // void remove_global_observer();

    // TODO(tommymchugh): Needs to be implemented but is not of high importance
    // Posts a native notification to the native notification manager
    void post_notification(const Notification notification);
};

};  // namespace notifications
};  // namespace sys
