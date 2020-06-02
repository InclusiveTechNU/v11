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
#include <thread>
#include <string>
#include "client/node/environment.h"
#include "client/node/utils.h"
#include "core/utils/run_main.h"
#include "core/environment/system/system.h"
#include "core/environment/system/platform/platform.h"
#include "core/environment/system/notifications/notification.h"
#include "core/environment/system/notifications/listener.h"

#define PLATFORM_TEXT_MAC "apple"
#define PLATFORM_TEXT_WINDOWS "windows"
#define PLATFORM_TEXT_LINUX "linux"
#define PLATFORM_TEXT_UNKNOWN "unknown"

using utils::string_from_value;
using sys::System;
using sys::notifications::Notification;
using sys::notifications::callback;
using sys::notifications::notification_type;
using sys::platform::platform;
using sys::platform::version;
using sys::platform::get_platform;
using sys::platform::get_platform_version;

namespace environment {

napi_status system(napi_env env, napi_value exports) {
    // Create system APIS for larkin
    // APIS within system include:
    //     - platform: platform specific information
    //     - notifications: App and sys notification listening
    napi_status status;

    // *****************************
    // *  PLATFORM API Interface
    // *****************************
    napi_value platform_object;
    status = napi_create_object(env, &platform_object);
    if (status != napi_ok) return status;

    // * platform.type -> string
    // Returns the specific platform larkin is running on
    // i.e. Apple, Windows, Linux, or Unknown
    napi_value platform_type;
    platform sys_platform = get_platform();
    std::string platform_str;
    if (sys_platform == platform::mac) {
        platform_str = PLATFORM_TEXT_MAC;
    } else if (sys_platform == platform::windows) {
        platform_str = PLATFORM_TEXT_WINDOWS;
    } else if (sys_platform == platform::linux) {
        platform_str = PLATFORM_TEXT_LINUX;
    } else {
        platform_str = PLATFORM_TEXT_UNKNOWN;
    }
    status = napi_create_string_utf8(env,
                                     platform_str.c_str(),
                                     NAPI_AUTO_LENGTH,
                                     &platform_type);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env,
                                     platform_object,
                                     "type",
                                     platform_type);
    if (status != napi_ok) return status;

    // * platform.version -> object
    // Returns information related to the platform version
    // Include major version, minor version, patch version, and
    // full string version
    version sys_version = get_platform_version();
    napi_value version, major_ver, minor_ver, patch_ver;
    status = napi_create_object(env, &version);
    if (status != napi_ok) return status;

    status = napi_create_uint32(env, sys_version.major_version, &major_ver);
    if (status != napi_ok) return status;
    status = napi_create_uint32(env, sys_version.minor_version, &minor_ver);
    if (status != napi_ok) return status;
    status = napi_create_uint32(env, sys_version.patch_version, &patch_ver);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env, version, "major", major_ver);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env, version, "minor", minor_ver);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env, version, "patch", patch_ver);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env, platform_object, "version", version);
    if (status != napi_ok) return status;

    // Declare and place platform api binding within v11.platform
    status = napi_set_named_property(env, exports, "platform", platform_object);
    if (status != napi_ok) return status;

    return status;
}

napi_status notifications(napi_env env, napi_value exports, System* sys_ptr) {
    // Create system APIS for larkin
    // APIS within system include:
    //     - platform: platform specific information
    //     - notifications: App and sys notification listening
    napi_status status;

    // *********************************
    // *  NOTIFICATIONS API Interface
    // *********************************
    napi_value notifications_object;
    status = napi_create_object(env, &notifications_object);
    if (status != napi_ok) return status;

    // * notifications.addEventListener(string, function) -> void
    // Calls a user defined callback function whenever a notification
    // type is registered by the system
    napi_value add_event_listener;
    status = napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        // Retrieve sys_ptr data
        napi_status status;
        void* sys_void_ptr = nullptr;
        napi_get_cb_info(env, info, nullptr, nullptr, nullptr, &sys_void_ptr);
        if (!sys_void_ptr) {
            // TODO(tommymchugh): Faill on system pointer cannot be found
            return nullptr;
        }
        System* sys_ptr = reinterpret_cast<System*>(sys_void_ptr);

        // TODO(tommymchugh): Evoke error on failed to collect arguments
        // Collect text and voice_id from info
        size_t args_count = 2;
        napi_value args[2];
        status = napi_get_cb_info(env, info, &args_count, args, nullptr, 0);
        if (status != napi_ok) return nullptr;

        napi_value listener_type_object = args[0];
        char* listener_type_ptr = string_from_value(env, listener_type_object);

        // TODO(tommymchugh): Figure out how to check for null for callback
        // Create async thread-safe callback function
        napi_value listener_callback_object = args[1];
        napi_threadsafe_function listener_callback;
        napi_value res_name;
        napi_create_string_utf8(env, "resource", NAPI_AUTO_LENGTH, &res_name);
        if (status != napi_ok) return nullptr;

        status = napi_create_threadsafe_function(env, listener_callback_object,
                                                 nullptr, res_name,
                                                 0, 2,
                                                 nullptr, nullptr, nullptr,
                                                 nullptr, &listener_callback);
        if (status != napi_ok) return nullptr;

        // Identify listener type
        if (!listener_type_ptr) {
            // TODO(tommymchugh): Implement catch all notification callback
            // ! Adds a callback function for all events
        } else {
            notification_type listener_type = notification_type::UNKNOWN;
            std::string type_str = std::string(listener_type_ptr);
            if (type_str == NOTIF_TYPE_APPLICATION_DID_HIDE) {
                listener_type = notification_type::APPLICATION_DID_HIDE;
            } else if (type_str == NOTIF_TYPE_APPLICATION_DID_LAUNCH) {
                listener_type = notification_type::APPLICATION_DID_LAUNCH;
            } else if (type_str == NOTIF_TYPE_APPLICATION_DID_TERMINATE) {
                listener_type = notification_type::APPLICATION_DID_TERMINATE;
            } else if (type_str == NOTIF_TYPE_APPLICATION_DID_UNHIDE) {
                listener_type = notification_type::APPLICATION_DID_UNHIDE;
            } else if (type_str == NOTIF_TYPE_DEVICE_DID_MOUNT) {
                listener_type = notification_type::DEVICE_DID_MOUNT;
            } else if (type_str == NOTIF_TYPE_DEVICE_DID_UNMOUNT) {
                listener_type = notification_type::DEVICE_DID_UNMOUNT;
            } else if (type_str == NOTIF_TYPE_SYSTEM_DID_WAKE) {
                listener_type = notification_type::SYSTEM_DID_WAKE;
            } else if (type_str == NOTIF_TYPE_SYSTEM_DID_SLEEP) {
                listener_type = notification_type::SYSTEM_DID_SLEEP;
            } else if (type_str == NOTIF_TYPE_SYSTEM_WILL_POWER_OFF) {
                listener_type = notification_type::SYSTEM_WILL_POWER_OFF;
            } else if (type_str == NOTIF_TYPE_ACCESSIBILITY_DID_CHANGE) {
                listener_type = notification_type::ACCESSIBILITY_DID_CHANGE;
            }

            // TODO(tommymchugh): callback func should delete at some point
            // Create the callback function from callback_object
            sys_ptr->add_event_listener(listener_type,
                                        [listener_callback]
                                        (Notification* notification) {
                napi_acquire_threadsafe_function(listener_callback);
                napi_call_threadsafe_function(listener_callback,
                                              nullptr,
                                              napi_tsfn_blocking);
            });
        }
        delete listener_type_ptr;
        return nullptr;
    }, sys_ptr, &add_event_listener);

    status = napi_set_named_property(env,
                                     notifications_object,
                                     "addEventListener",
                                     add_event_listener);
    if (status != napi_ok) return status;

    // Declare and place platform api binding within v11.notifications
    status = napi_set_named_property(env,
                                     exports,
                                     "notifications",
                                     notifications_object);
    if (status != napi_ok) return status;
    return status;
}

// Initialize all variables and functions
void init(napi_env env, napi_value exports, System* sys_ptr) {
    napi_status system_status = system(env, exports);
    if (system_status != napi_ok) {
        napi_throw_error(env,
                         nullptr,
                         "Failed to initialize environment/system");
        return;
    }

    napi_status notifications_status = notifications(env, exports, sys_ptr);
    if (notifications_status != napi_ok) {
        napi_throw_error(env,
                         nullptr,
                         "Failed to initialize environment/notifications");
        return;
    }
}

};  // namespace environment
