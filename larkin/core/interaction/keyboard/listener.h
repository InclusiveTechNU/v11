/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <sys/types.h>
#include <functional>
#include "interaction/keyboard/keycode.h"
#include "interaction/keyboard/keyboard_event.h"

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
    callback callback;
};

};  // namespace keyboard
