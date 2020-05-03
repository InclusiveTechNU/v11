/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "utils/definitions.h"
#include "environment/system/notifications/notification_manager.h"

using utils::error_code;
using utils::error;

namespace sys {
namespace notifications {

NotificationManager::NotificationManager(manager_type type) : type(type) {
    global_event_observer = get_global_event_observer();
    register_global_event_observer();
}

global_observer NotificationManager::get_global_event_observer() {
    global_observer event_observer = [&] (Notification* observed_event) {
        // * To print notification name
        // * print(observed_event->get_native_name());

        for (int i = 0; i < event_listeners.size(); i++) {
            listener& event_listener = event_listeners[i];
            if (event_listener.name == observed_event->get_name()) {
                event_listener.callback(observed_event);
                observed_event->release();
            }
        }
    };

    return event_observer;
}

NotificationManager* NotificationManager::get_system_center() {
    NotificationManager* system_manager = new NotificationManager(system);
    return system_manager;
}

utils::error NotificationManager::register_global_event_observer() {
    bridge = NotificationManagerBridge::create_bridge(type);
    if (!bridge) {
        return {
            true,
            error_code::ERROR_FAILED_LINKING_MANAGER_BRIDGE
        };
    }

    return bridge->register_global_observer(global_event_observer);
}

void NotificationManager::add_event_listener(const listener& event_listener) {
    event_listeners.push_back(event_listener);
}

NotificationManager::~NotificationManager() {
    /* !! See notification_manager_bridge.h !!
    if (bridge) {
        bridge->remove_global_observer();
    }*/

    delete bridge;
}

};  // namespace notifications
};  // namespace sys
