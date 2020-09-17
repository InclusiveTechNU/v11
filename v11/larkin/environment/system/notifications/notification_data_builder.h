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

#include "larkin/environment/system/notifications/notification.h"

namespace sys {
namespace notifications {

// Provides a factory class for building a NotificationData object. 
class NotificationDataBuilder : public NotificationData {
 private:
    NotificationDataBuilder() = default;

    // The specific data type that the data value should be cast to when
    // returned through the GetData method.
    notification_data_type data_type_ = notification_data_type::kUnknown;

    // The data stored by the resulting NotificationData class. Data is owned
    // by the NotificationData object and is released when the owner
    // is released from memory.
    void* data_value_ = nullptr;

 public:
    ~NotificationDataBuilder();

    // Creates a reference to a NotificationDataBuilder object and passes
    // ownership of the object back to the caller.
    static NotificationDataBuilder* Create();

    // Casts the current builder object as a NotificationData object and
    // returns this object as a pointer. Transfers ownership of this object
    // to the caller.
    NotificationData* Build();

    // Transfers ownership of the data to the NotificationData class and
    // places it within the class as the data_value_ variable. If there is
    // already a stored data value in the class, that value is released from
    // memory.
    void PutData(notification_data_type type, void* data);

    // From NotificationData class
    notification_data_type GetType() const;
    const void* GetData() const;
};

}  // namespace notifications
}  // namespace sys
