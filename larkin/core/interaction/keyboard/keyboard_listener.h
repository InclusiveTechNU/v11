/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <vector>
#include "interaction/keyboard/keyboard_event.h"
#include "interaction/keyboard/listener.h"
#include "interaction/keyboard/keyboard_listener_bridge.h"

using keyboard::event::event_type;

namespace keyboard {

// Manages through adding and removing keyboard event
// listeners
class KeyboardListener {
    // The native bridge interface that controls the
    // platform dependent keyboard listener functionality
    KeyboardListenerBridge* native_bridge = nullptr;
    // The current event listeners that are checked for
    // each time the global event observer is called
    std::vector<listener> event_listeners;
    // The next id set for the event listener added to this
    // class instance
    pid_t next_listener_id = 0;
    // The global event observer which processes incoming
    // events and sorts the event to the correct registered
    // event listener if one matches.
    global_observer* global_event_observer;

 public:
    // TODO(tommymchugh): Add remove listener method
    // Registers the global event observer and the bridge.
    // connects the global event observer to the keyboard listener
    // bridge interface
    KeyboardListener();

    // Adds a new keyboard event listener to the event listeners vector which
    // will be checked every time the global event observer processes a new
    // incoming event.
    void add_event_listener(const event_type& type, const callback& callback);

    // Destroys the native memory management instances through the
    // keyboard listener bridge interface and frees the global event observer
    ~KeyboardListener();
};

};  // namespace keyboard
