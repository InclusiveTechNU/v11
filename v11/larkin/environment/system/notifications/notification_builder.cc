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

#include "environment/system/notifications/notification_builder.h"

namespace sys {
namespace notifications {

NotificationBuilder::NotificationBuilder() {
    data_ = new absl::flat_hash_map<std::string, int>;
}

NotificationBuilder::~NotificationBuilder() {
    delete data_;
}

// Creates a reference to a NotificationBuilder object and passes
// ownership of the object back to the caller.
NotificationBuilder* NotificationBuilder::Create() {
    return new NotificationBuilder;
}

// Casts the current builder object as a Notification object and returns 
// this object as a pointer. Transfers ownership of this object to
// the caller.
Notification* NotificationBuilder::Build() {
    return this;
}

// Changes the built notification type to the value of 'type'
void NotificationBuilder::SetType(notification_type type) {
    type_ = type;
}

// Returns the specific type of action identifier that the notification
// is linked to.
notification_type NotificationBuilder::GetType() {
    return type_;
}

}  // namespace notifications
}  // namespace sys
