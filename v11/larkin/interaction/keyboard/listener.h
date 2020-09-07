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

#include <sys/types.h>
#include <functional>
#include "larkin/interaction/keyboard/keycode.h"
#include "larkin/interaction/keyboard/keyboard_event.h"

namespace keyboard {

// A function that distributes incoming observed events
// to specific callbacks that are attached to observing events.
typedef std::function<void(event::KeyboardEvent*)> global_observer;

// Listener callback function that is called when
// event is triggered. Returns the keyboard event that was observed.
// ! After performing callback on event it is released
typedef const std::function<void(event::KeyboardEvent*)> callback;

// A structure to hold information relevant to keyboard event listeners.
//     `type`: The type of keyboard event being listened for
//     `id`:  A manager specific id for the listener data
//     `callback`: A function called when the event is observed
struct listener {
    event::event_type type;
    pid_t id;
    keyboard::callback callback;
};

};  // namespace keyboard
