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

#include <vector>
#include "larkin/interaction/keyboard/keycode.h"
#include "larkin/interaction/keyboard/keyboard_simulator_bridge.h"

namespace keyboard {

// Simulates native keyboard key presses and holds
class KeyboardSimulator {
    // The interface to the native platform commands to
    // control keybaord key simulation
    KeyboardSimulatorBridge* bridge = nullptr;

 public:
    // Allocates a native bridge instance
    KeyboardSimulator();

    // Presses up and down a vector of keys
    void press_keys(const std::vector<keycode>& keys);
    // Presses up and down a single key
    void press_key(const keycode& key);

    // Presses down and holds a vector of key for later release
    void hold_keys(const std::vector<keycode>& keys);
    // Presses down and holds a key for later release
    void hold_key(const keycode& key);

    // Releases a held down a vector of keys if they are being held
    void release_keys(const std::vector<keycode>& keys);
    // Releases a held down key if it is being held
    void release_key(const keycode& key);

    // Sends the native memory of the bridge instance back to
    // the native memory reference manager
    ~KeyboardSimulator();
};

};  // namespace keyboard
