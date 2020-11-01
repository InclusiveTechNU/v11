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

#include <map>
#include "core/interaction/keyboard/keycode.h"

namespace keyboard {

// A pointer to a native key event
// such as key down and key up events
typedef void* native_key_event;

// The native interface for simulating keyboard
// events such as key presses, holds, and releases
class KeyboardSimulatorBridge {
    // A collection of currently active key events
    // stored by the core keycode value
    std::map<keycode, native_key_event> key_events;

 public:
    // Sends a request to hold a keyboard down event
    // until the key is released by the bridge. Does
    // nothing if the key is already held down
    // ! Does not check whether key is being held
    void hold_key(const keycode& key);
    // Sends a request to send a keyboard up event for
    // the keycode specified releasing the event from
    // the bridge. Does nothing if the key is not being
    // held down
    // ! Does not check whether key is not being held
    void release_key(const keycode& key);
    // Checks if there is currently a key event that is
    // blocking for the current key
    bool keycode_free(const keycode& key);
};

}  // namespace keyboard
