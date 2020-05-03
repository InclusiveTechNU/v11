/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "environment/system/system.h"

namespace sys {

System::System(): platform(platform::get_platform_info()),
                  notification_center(NotificationManager::
                                      get_system_center()) {
    bridge = new SystemBridge;
    pending_actions = bridge->get_pending_actions();
    keyboard_listener = bridge->get_keyboard_listener();
}

void System::add_event_listener(const keyboard::event::
                                      event_type& action,
                                const keyboard::callback& callback) {
    if (keyboard_listener) {
        keyboard_listener->add_event_listener(action, callback);
    } else {
        if (pending_actions) {
            (*pending_actions).push_back(new std::function<void(void*)>(
            [&](void* kb_listener) {
                reinterpret_cast<KeyboardListener*>
                (kb_listener)->add_event_listener(action, callback);
            }));
        }
    }
}
void System::add_event_listener(const notifications::notification_type& action,
                                const notifications::callback& callback) {
    notification_center->add_event_listener({
        action,
        0,
        callback
    });
}

System::~System() {
    if (bridge) {
        bridge->remove_all_pending_actions();
    }
    delete notification_center;
    delete bridge;
}

};  // namespace sys
