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

#include "larkin/environment/system/notifications/notification_data_builder.h"

namespace sys {
namespace notifications {

NotificationDataBuilder::~NotificationDataBuilder() {
    delete data_value_;
}

NotificationDataBuilder* NotificationDataBuilder::Create() {
    return new NotificationDataBuilder;
}

NotificationData* NotificationDataBuilder::Build() {
    return this;
}

void NotificationDataBuilder::PutData(notification_data_type type,
                                      void* data) {
    delete data_value_;
    data_value_ = data;
    data_type_ = type;
}

notification_data_type NotificationDataBuilder::GetType() const {
    return data_type_;
}
const void* NotificationDataBuilder::GetData() const {
    return data_value_;
}

}  // namespace notifications
}  // namespace sys
