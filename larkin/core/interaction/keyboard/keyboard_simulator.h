/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <vector>
#include "interaction/keyboard/keycode.h"
#include "interaction/keyboard/keyboard_simulator_bridge.h"

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
