/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <sys/types.h>
#include <functional>
#include "environment/system/notifications/notification.h"

namespace sys {
namespace notifications {

// A function that distributes incoming observed notifications
// to specific callbacks that are attached to observing events.
typedef std::function<void(Notification*)> global_observer;

// Listener callback function that is called when
// event is triggered. Returns the notification that was observed.
// ! After performing callback on notification it is released
typedef const std::function<void(Notification*)> callback;

// A structure to hold information relevant to notification
// event listeners.
//     `name`: The type of notification being listened for
//     `id`:  A manager specific id for the listener data
//     `callback`: A function called when the event is observed
struct listener {
    notification_type name;
    pid_t id;
    callback callback;
};

};  // namespace notifications
};  // namespace sys
