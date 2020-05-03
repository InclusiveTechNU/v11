/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

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

std::string Notification::get_data_with_key(const std::string& key) {
    return notification_data.at(key);
}

void Notification::put_data_with_key(const std::string& key,
                                     const std::string& data) {
    notification_data.insert(std::pair<std::string, std::string>(key, data));
}

void Notification::release() {
    delete native_name;
    delete this;
}

};  // namespace notifications
};  // namespace sys
