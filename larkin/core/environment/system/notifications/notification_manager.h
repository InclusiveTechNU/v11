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
#include <vector>
#include "utils/error.h"
#include "environment/system/notifications/listener.h"
#include "environment/system/notifications/manager_type.h"
#include "environment/system/notifications/notification_manager_bridge.h"

using utils::error;

namespace sys {
namespace notifications {

// TODO(tommymchugh): I'm not sure about whether this should be
// events instead of notifications so that we can have notifications
// be for actual popup alert notifications.

class NotificationManager {
 private:
    // Identifies the type of manager system or custom
    manager_type type;

    // Counter for generating pids
    pid_t next_pid = 0;

    // An array of event_listeners to check on each time
    // the global event observer is called
    std::vector<listener> event_listeners;

    // Function run on every event observed that checks for
    // notifications from `event_listeners`.
    global_observer global_event_observer;

    // A connection to retrieve notification data from the
    // native platform's notification manager
    NotificationManagerBridge* bridge = nullptr;

    // Attaches a function that managers larkin notification
    // processing to the native notification manager.
    error register_global_event_observer();

    // Returns a pointer for the global event observer
    // to manage all existing event listener actions. Transfers
    // ownership to the caller.
    global_observer get_global_event_observer();

 public:
    // Creates a notification manager for the specific system
    // platform depending on the `manager_type`. Forwards
    // all notification messages to the manager to be processes.
    explicit NotificationManager(manager_type type);

    // TODO(tommymchugh): This should switch to callback and event params
    // Adds an event listener to be checked from the
    // global event observer
    void add_event_listener(const listener& event_listener);

    // Allocates memory for a new NotificationManager(system) type.
    // Transfers ownership to the caller.
    static NotificationManager *get_system_center();

    // Frees the bridge from memory
    ~NotificationManager();
};

};  // namespace notifications
};  // namespace sys
