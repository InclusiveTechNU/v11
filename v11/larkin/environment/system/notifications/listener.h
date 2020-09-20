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
#include "larkin/environment/system/notifications/notification.h"

namespace sys {

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
    sys::callback callback;
};

}  // namespace sys
