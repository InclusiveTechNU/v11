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

#include "interaction/keyboard/keycode.h"

namespace keyboard {
namespace event {

// The different keyboard event listener types
// that are supported by Larkin's corss platform
// event listener
enum event_type {
    KEY_DOWN,
    KEY_UP
};

// Holds data regarding a keyboard event that Larkin was notified
// of such as press type (up or down) and the key being pressed
// TODO(tommymchugh): Record information about event source application
class KeyboardEvent {
    // The type of keyboard event that was recorded
    // such as key up or key down
    event_type press_type;
    // The specific key from the keyboard that is activating
    // the target keyboard event
    keycode target_key;
 public:
    // Creates a keyboard event with a specific event press type
    // and the specific key causing the event
    KeyboardEvent(const event_type& press_type, const keycode& target_key);
    // Returns the specific keyboard event that was identified
    const event_type& get_event_type();
    // Returns the key that activated the keyboard event
    const keycode& get_event_target_key();
};

};  // namespace event
};  // namespace keyboard
