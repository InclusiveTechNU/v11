/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <sys/types.h>
#include <string>
#include <functional>
#include <map>

namespace sys {
namespace notifications {

// Platform indepdent notification identifier names
enum notification_type {
    UNKNOWN,
    APPLICATION_DID_LAUNCH,
    APPLICATION_DID_TERMINATE,
    APPLICATION_DID_HIDE,
    APPLICATION_DID_UNHIDE,
    DEVICE_DID_MOUNT,
    DEVICE_DID_UNMOUNT,
    SYSTEM_DID_WAKE,
    SYSTEM_DID_SLEEP,
    SYSTEM_WILL_POWER_OFF,
    SYSTEM_ACCESSIBILITY_DISPLAY_DID_CHANGE
};

// A platform indepdent structure containining the
// details of the observed notification.
class Notification {
 private:
    notification_type name;
    char* native_name;
    std::map<std::string, std::string> notification_data;
 public:
    Notification(const char* name, notification_type type);

    const notification_type& get_name();
    const char* get_native_name();

    std::string get_data_with_key(const std::string& key);
    void put_data_with_key(const std::string& key, const std::string& data);

    // Releases the current object from memory.
    // ! notification objects should always be acquired from `new`
    void release();
};

};  // namespace notifications
};  // namespace sys
