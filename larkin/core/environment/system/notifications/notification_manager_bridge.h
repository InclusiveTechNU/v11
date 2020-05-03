/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <functional>
#include "utils/error.h"
#include "environment/system/notifications/listener.h"
#include "environment/system/notifications/notification.h"
#include "environment/system/notifications/manager_type.h"

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
