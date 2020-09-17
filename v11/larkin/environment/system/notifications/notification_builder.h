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
#include "absl/container/flat_hash_map.h"
#include "environment/system/notifications/notification.h"

namespace sys {
namespace notifications {

// A platform indepdent structure containining the
// details of the observed notification.
class NotificationBuilder : public Notification {
 private:
     NotificationBuilder();

    // The specific supported type of system/custom notification that
    // this particular notification is linked to.
    notification_type type_ = notification_type::kUnknown;

    // An unsorted map of NotificationData objects stored with the
    // notification. Data objects are owned by the Notification and
    // are destroyed on release.
    absl::flat_hash_map<std::string, int>* data_ = nullptr;
    
 public:
    ~NotificationBuilder();

    // Creates a reference to a NotificationBuilder object and passes
    // ownership of the object back to the caller.
    static NotificationBuilder* Create();

    // Casts the current builder object as a Notification object and returns 
    // this object as a pointer. Transfers ownership of this object to
    // the caller.
    Notification* Build();

    // Changes the built notification type to the value of 'type'
    void SetType(notification_type type);

    // From Notification class
    notification_type GetType();
};

}  // namespace notifications
}  // namespace sys
