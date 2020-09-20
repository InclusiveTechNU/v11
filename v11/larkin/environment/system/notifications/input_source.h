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

#include <string>
#include <vector>
#include <functional>
#include "larkin/environment/system/notifications/notification.h"

namespace sys {

// Callback function passed back when an input source recevies
// a new notification
typedef std::function<void(const Notification*)> InputSourceCallback;

// Settings that control notification input management procedures.
// Used primarily by InputSource classes.
struct InputSourceSettings {
    // Whether the InputSource class is accepting input
    bool enabled = false;

    // Whether the InputSource class should store notifications
    // in memory.
    bool store_memory = false;
};

// Transformer for abstract notifications into structured data that can be
// processed by a NotificationManager class. Most managers have one or more
// InputSources attached to them to handle event listeners.
class InputSource {
 public:
    virtual ~InputSource() {};

    // Updates the input source's callback function. This function is called
    // whenever a new notification is received and the notification is passed
    // through the callback before being released from memory.
    virtual void SetCallback(InputSourceCallback* callback) = 0;

    // Returns the settings that control how and when notifications are
    // received and handled by the InputSource object.
    virtual const InputSourceSettings& GetSettings() const = 0;

    // Returns whether the InputSource is currently accepting and handling
    // new notifications.
    virtual bool IsEnabled() const = 0;

    // Changes the InputSource object's enabled settings to the value
    // of 'enabled'.
    virtual void SetEnabled(bool enabled) = 0;

    // Returns whether the InputSource is storing notifications in memory
    // after receiving them.
    virtual bool IsStoringMemory() const = 0;

    // Sets the InputSource objects's storage setting to the value
    // of 'storing'.
    virtual void SetStoringMemory(bool storing) = 0;

    // Clears any notifications from the InputSource objects' internal memory.
    virtual void ClearMemory() = 0;

    // Returns a constant pointer to the object's internal notification
    // memory vector.
    virtual const std::vector<Notification*>* GetMemory() const = 0;

    // Returns the name of the InputSource object's notification source.
    virtual const std::string& GetInputSourceName() const = 0;
};

}  // namespace sys
