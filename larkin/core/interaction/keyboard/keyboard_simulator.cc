/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "interaction/keyboard/keyboard_simulator.h"

namespace keyboard {

// TODO(tommymchugh): Check for press keys and hold_keys to include
// an option or a shift or something like that and add the special method
// in the native interface

KeyboardSimulator::KeyboardSimulator() {
    bridge = new KeyboardSimulatorBridge;
}

void KeyboardSimulator::press_keys(const std::vector<keycode>& keys) {
    for (const keycode& key : keys) {
        hold_key(key);
    }
    for (const keycode& key : keys) {
        release_key(key);
    }
}

void KeyboardSimulator::press_key(const keycode& key) {
    hold_key(key);
    release_key(key);
}

void KeyboardSimulator::hold_keys(const std::vector<keycode>& keys) {
    for (const keycode& key : keys) {
        hold_key(key);
    }
}

void KeyboardSimulator::hold_key(const keycode& key) {
    if (bridge->keycode_free(key)) {
        bridge->hold_key(key);
    }
}

void KeyboardSimulator::release_keys(const std::vector<keycode>& keys) {
    for (const keycode& key : keys) {
        release_key(key);
    }
}

void KeyboardSimulator::release_key(const keycode& key) {
    if (!bridge->keycode_free(key)) {
        bridge->release_key(key);
    }
}

KeyboardSimulator::~KeyboardSimulator() {
    delete bridge;
}

};  // namespace keyboard
