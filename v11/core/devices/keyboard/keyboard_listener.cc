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

#include <stdio.h>
#include "core/devices/keyboard/keyboard_listener.h"
#include "utils/definitions.h"

namespace keyboard {

KeyboardListener::KeyboardListener() {
    native_bridge = new KeyboardListenerBridge;
    global_event_observer = new global_observer(
                            [&](event::KeyboardEvent* event) {
        const listener* last_listener = nullptr;
        for (const listener& event_listener : event_listeners) {
            if (event->get_event_type() == event_listener.type) {
                event_listener.callback(event);
            }
        }
    });
    native_bridge->register_global_observer(global_event_observer);
}

void KeyboardListener::add_event_listener(const event_type& type,
                                          const callback& callback) {
    event_listeners.push_back({type, next_listener_id, callback});
    next_listener_id++;
}

KeyboardListener::~KeyboardListener() {
    delete native_bridge;
    delete global_event_observer;
}

}  // namespace keyboard
