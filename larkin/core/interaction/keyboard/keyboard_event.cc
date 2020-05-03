/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "interaction/keyboard/keyboard_event.h"

namespace keyboard {
namespace event {

KeyboardEvent::KeyboardEvent(const event_type& press_type,
                             const keycode& target_key):
                            press_type(press_type),
                            target_key(target_key) {   }

const event_type& KeyboardEvent::get_event_type() {
    return press_type;
}

const keycode& KeyboardEvent::get_event_target_key() {
    return target_key;
}

};  // namespace event
};  // namespace keyboard
