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
