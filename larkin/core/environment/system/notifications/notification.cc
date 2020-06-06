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

#include <iostream>
#include <string.h>
#include <utility>
#include "environment/system/notifications/notification.h"

namespace sys {
namespace notifications {

Notification::Notification(const char* name, notification_type type) :
                                                          name(type) {
    native_name = new char[strlen(name)+1];
    for (int i = 0; name[i] != '\0'; i++) {
        native_name[i] = name[i];
    }
}

const notification_type& Notification::get_name() {
    return name;
}

const char* Notification::get_native_name() {
    return native_name;
}

std::map<std::string, std::string> Notification::
                                   get_notification_data() const {
    return notification_data;
}

std::string Notification::get_data_with_key(const std::string& key) const {
    return notification_data.at(key);
}

void Notification::put_data_with_key(const std::string& key,
                                     const std::string& data) {
    notification_data.insert(std::pair<std::string, std::string>(key, data));
}

void Notification::release() {
    delete native_name;
    native_name = nullptr;
}

Notification::~Notification() {
    release();
}

};  // namespace notifications
};  // namespace sys
