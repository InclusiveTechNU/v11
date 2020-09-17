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

namespace sys {
namespace notifications {

// Platform indepdent notification identifier names
enum notification_type {
    UNKNOWN,

    // Hardware Notifications    
    DEVICE_DID_MOUNT,
    DEVICE_DID_UNMOUNT,

    // System Notifications
    SYSTEM_DID_WAKE,
    SYSTEM_DID_SLEEP,
    SYSTEM_WILL_POWER_OFF,

    // Accessibility Notifications
    ACCESSIBILITY_DID_CHANGE,

    // Application Lifecycle Notifications
    APPLICATION_DID_LAUNCH,
    APPLICATION_DID_TERMINATE,
    APPLICATION_DID_HIDE,
    APPLICATION_DID_UNHIDE,
    APPLICATION_DID_CHANGE_MAIN_WINDOW,
    APPLICATION_DID_CHANGE_FOCUSED_WINDOW,
    APPLICATION_DID_CHANGE_FOCUSED_UI_ELEMENT,
    APPLICATION_DID_CREATE_UI_ELEMENT,
    APPLICATION_DID_CREATE_WINDOW,
    APPLICATION_DID_REMOVE_ELEMENT,

    // Window Element Notifications
    WINDOW_ELEMENT_DID_FINISH_MOVE,
    WINDOW_ELEMENT_DID_FINISH_RESIZE,
    WINDOW_ELEMENT_DID_MINIMIZE,
    WINDOW_ELEMENT_DID_DEMINIMIZE,

    // Application UI Element Notifications
    UI_ELEMENT_DID_RESIZE,
    UI_ELEMENT_DID_MOVE,
    UI_ELEMENT_DID_CHANGE_TITLE,
    UI_ELEMENT_DID_CHANGE_VALUE,
    UI_ELEMENT_REMOVED
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
    ~Notification();

    const notification_type& get_name();
    const char* get_native_name();

    std::map<std::string, std::string> get_notification_data() const;
    std::string get_data_with_key(const std::string& key) const;
    void put_data_with_key(const std::string& key, const std::string& data);

    // Releases the current object from memory.
    // ! notification objects should always be acquired from `new`
    void release();
};

}  // namespace notifications
}  // namespace sys
