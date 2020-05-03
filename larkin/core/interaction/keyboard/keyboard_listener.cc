/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "interaction/keyboard/keyboard_listener.h"
#include "utils/definitions.h"

namespace keyboard {

KeyboardListener::KeyboardListener() {
    native_bridge = new KeyboardListenerBridge;
    global_event_observer = new global_observer(
                            [&](event::KeyboardEvent* event) {
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

};  // namespace keyboard
