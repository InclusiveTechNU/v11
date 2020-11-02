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

#include <list>
#include "utils/error.h"
#include "core/devices/keyboard/listener.h"

using utils::error;

namespace keyboard {

// Native memory locations for the event listeners
// that are monitoring keyboard events. Memory
// for each location has transferred ownership to
// Core.
typedef void* monitor_event;

// Stores data to be used to delete activated keycodes
// when they must be removed from the native listener
// bridge interface
struct keycode_index {
    bool activated = false;
    std::list<keycode>::iterator index;
};

// A bridge to attach keyboard event listeners
// to native keyboard manager apis and tooling
class KeyboardListenerBridge {
    // A list of native events being monitored that
    // require to be released to native memory management
    // on class destruction
    monitor_event monitoring_event_;
    // Stores the keycodes that are currently being pressed
    // from native keyboard listening events
    std::list<keycode> activated_keycodes_;
    // The global event observer that controls which callback
    // functions are called when a new native event is transferred
    // to the Core keyboard listener.
    const global_observer* observer_ = nullptr;
    // Whether the global observer pointer has been transferred
    // to the current listener bridge instance
    bool registered_global_observer_ = false;
    // Returns the keycode index data for the specified keycode or
    // alerts that the key is not activated if not found inside
    // activated_keycodes_
    const keycode_index keycode_activated(const keycode& code);

 public:
    // Adds the global observer to the native event listener service
    // if the global observer is not always registered
    error register_global_observer(const global_observer* observer);

    // Removes all native event keyboard listeners and transfers ownership
    // of the removed systems back to the native memory management system
    // where they will be removed.
    // ! The global observer is owned by the listener and so it will not be
    // ! freed on destruction
    ~KeyboardListenerBridge();
};

}  // namespace keyboard
