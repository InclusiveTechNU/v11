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
#include <string>
#include <functional>
#include <map>

#define NOTIF_TYPE_UNKNOWN "unknown"
#define NOTIF_TYPE_APPLICATION_DID_LAUNCH "launch"
#define NOTIF_TYPE_APPLICATION_DID_TERMINATE "terminate"
#define NOTIF_TYPE_APPLICATION_DID_HIDE "hide"
#define NOTIF_TYPE_APPLICATION_DID_UNHIDE "unhide"
#define NOTIF_TYPE_DEVICE_DID_MOUNT "mount"
#define NOTIF_TYPE_DEVICE_DID_UNMOUNT "unmount"
#define NOTIF_TYPE_SYSTEM_DID_WAKE "wake"
#define NOTIF_TYPE_SYSTEM_DID_SLEEP "sleep"
#define NOTIF_TYPE_SYSTEM_WILL_POWER_OFF "poweroff"
#define NOTIF_TYPE_SYSTEM_ACCESSIBILITY_DISPLAY_DID_CHANGE "accessibility"

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
