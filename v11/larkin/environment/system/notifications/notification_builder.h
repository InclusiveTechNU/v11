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
#include "absl/container/flat_hash_set.h"
#include "larkin/environment/system/notifications/notification.h"

namespace sys {

// A factory class for generating a Notification class object. Provides
// methods for customizing the inner objects of the Notification class
// and exposing those values to a Notification object.
class NotificationBuilder : public Notification {
 private:
     NotificationBuilder();

    // The specific supported type of system/custom notification that
    // this particular notification is linked to.
    NotificationType type_ = NotificationType::kUnknown;

    // An unsorted map of NotificationData objects stored with the
    // notification. Data objects are owned by the Notification and
    // are destroyed on release.
    absl::flat_hash_map<std::string, NotificationData*>* data_ = nullptr;

    // An unsorted map of keys that is kept as a record of keys that
    // are data elements for the notification's data object.
    absl::flat_hash_set<std::string>* keys_ = nullptr;

 public:
    ~NotificationBuilder();

    // Creates a reference to a NotificationBuilder object and passes
    // ownership of the object back to the caller.
    static NotificationBuilder* Create();

    // TODO(tommymchugh): Clone instead of cast
    // Clones the current builder object as a new Notification object and
    // returns this object as a pointer. Transfers ownership of this object
    // to the caller.
    Notification* Build();

    // Returns a pointer to the notification's data object. This does not
    // transfer ownership of the data object. This is always owned by the
    // notification builder.
    const absl::flat_hash_map<std::string, NotificationData*>* GetDataMap() const;

    // Adds or replaces an entry in the notification's data with key 'key'
    // and data of object 'value'.
    void PutData(const std::string& key, NotificationData* value);

    // Changes the built notification type to the value of 'type'
    void SetType(NotificationType type);

    // From Notification class
    NotificationType GetType() const;
    const absl::flat_hash_set<std::string>* GetDataKeys() const;
    const NotificationData* GetData(const std::string& key) const;
};

}  // namespace sys
