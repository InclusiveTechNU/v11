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

#include "environment/system/system.h"

namespace sys {

System::System(): platform(platform::get_platform_info()),
                  notification_center(NotificationManager::
                                      get_system_center()) {
    bridge = new SystemBridge;
    pending_actions = bridge->get_pending_actions();
    keyboard_listener = bridge->get_keyboard_listener();
}

NotificationManager* System::get_notification_center() {
    return notification_center;
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
