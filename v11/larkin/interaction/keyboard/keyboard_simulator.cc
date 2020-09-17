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

#include "larkin/interaction/keyboard/keyboard_simulator.h"

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

}  // namespace keyboard
