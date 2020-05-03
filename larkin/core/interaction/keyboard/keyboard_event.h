/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
