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
#include <string>
#include <vector>
#include "runtime/node/environment.h"
#include "runtime/node/utils.h"
#include "utils/run_main.h"
#include "core/system/system.h"
#include "core/system/system_instance.h"
#include "core/system/platform/platform.h"
#include "core/system/notifications/system_notification.h"
#include "core/system/notifications/system_notification_manager.h"
#include "core/applications/application.h"

#define PLATFORM_TEXT_MAC "apple"
#define PLATFORM_TEXT_WINDOWS "windows"
#define PLATFORM_TEXT_LINUX "linux"
#define PLATFORM_TEXT_UNKNOWN "unknown"

using utils::application_to_object;
using utils::notification_to_object;
using utils::string_from_value;
using sys::System;
using sys::SystemInstance;
using sys::SystemNotification;
using sys::SystemNotificationType;
using sys::SystemNotificationManager;
using sys::SystemNotificationCallback;
using sys::NotificationType;
using sys::NotificationCallback;
using sys::Platform;
using sys::Version;
using sys::OperatingSystem;
using app::Application;

// TODO(tommymchugh): This should be moved somewhere else
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
#define NOTIF_TYPE_ACCESSIBILITY_DID_CHANGE "accessibility"

namespace environment {

SystemNotificationType string_to_notification_type(std::string type_str) {
    if (type_str == NOTIF_TYPE_APPLICATION_DID_HIDE) {
        return SystemNotificationType::kApplicationDidHide;
    } else if (type_str == NOTIF_TYPE_APPLICATION_DID_LAUNCH) {
        return SystemNotificationType::kApplicationDidLaunch;
    } else if (type_str == NOTIF_TYPE_APPLICATION_DID_TERMINATE) {
        return SystemNotificationType::kApplicationDidTerminate;
    } else if (type_str == NOTIF_TYPE_APPLICATION_DID_UNHIDE) {
        return SystemNotificationType::kApplicationDidUnhide;
    } else if (type_str == NOTIF_TYPE_DEVICE_DID_MOUNT) {
        return SystemNotificationType::kDeviceDidMount;
    } else if (type_str == NOTIF_TYPE_DEVICE_DID_UNMOUNT) {
        return SystemNotificationType::kDeviceDidUnmount;
    } else if (type_str == NOTIF_TYPE_SYSTEM_DID_WAKE) {
        return SystemNotificationType::kSystemDidWake;
    } else if (type_str == NOTIF_TYPE_SYSTEM_DID_SLEEP) {
        return SystemNotificationType::kSystemDidSleep;
    } else if (type_str == NOTIF_TYPE_SYSTEM_WILL_POWER_OFF) {
        return SystemNotificationType::kSystemWillPowerOff;
    } else if (type_str == NOTIF_TYPE_ACCESSIBILITY_DID_CHANGE) {
        return SystemNotificationType::kAccessibilityDidChange;
    } else {
        return SystemNotificationType::kUnknownSystemNotification;
    }
}

napi_status system(napi_env env, napi_value exports) {
    // Create system APIS for core
    // APIS within system include:
    //     - platform: platform specific information
    //     - notifications: App and sys notification listening
    napi_status status;

    // *****************************
    // *  APPLICATION API Interface
    // *****************************
    napi_value applications;
    a_ok(napi_create_object(env, &applications));

    napi_value activate;
    napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        size_t args_count = 1;
        napi_value args[1];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value process_id_val = args[0];
        pid_t process_id;
        a_ok(napi_get_value_int32(env, process_id_val, &process_id));
        Application(process_id).activate();
        return nullptr;
    }, nullptr, &activate);
    a_ok(napi_set_named_property(env,
                                 applications,
                                 "activate",
                                 activate));

    // * applications.getApplications() -> Array<Object>
    napi_value get_applications;
    napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        napi_value application_array;
        a_ok(napi_create_array(env, &application_array));
        std::vector<Application*> applications = Application::
                                                 get_active_applications();
        for (std::size_t i = 0; i < applications.size(); i++) {
            const Application* app = applications[i];
            napi_value app_object;
            application_to_object(env, app, &app_object);
            a_ok(napi_set_element(env, application_array, i, app_object));
        }
        return application_array;
    }, nullptr, &get_applications);
    a_ok(napi_set_named_property(env,
                                 applications,
                                 "getApplications",
                                 get_applications));
    a_ok(napi_set_named_property(env,
                                 exports,
                                 "applications",
                                 applications));

    // *****************************
    // *  PLATFORM API Interface
    // *****************************
    napi_value platform_object;
    status = napi_create_object(env, &platform_object);
    if (status != napi_ok) return status;

    // * platform.type -> string
    // Returns the specific platform core is running on
    // i.e. Apple, Windows, Linux, or Unknown
    napi_value platform_type;
    std::string platform_str;
    System* sys_ptr = SystemInstance::GetInstance();
    const Platform* platform = sys_ptr->GetPlatform();
    OperatingSystem sys_platform = platform->GetOperatingSystem();
    Version sys_version = platform->GetVersion();

    if (sys_platform == OperatingSystem::kMac) {
        platform_str = PLATFORM_TEXT_MAC;
    } else if (sys_platform == OperatingSystem::kWindows) {
        platform_str = PLATFORM_TEXT_WINDOWS;
    } else if (sys_platform == OperatingSystem::kLinux) {
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
    status = napi_set_named_property(env,
                                     exports,
                                     "platform",
                                     platform_object);
    if (status != napi_ok) return status;

    return status;
}

napi_status notifications(napi_env env, napi_value exports) {
    // Create system APIS for core
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

        napi_value listener_type_val = args[0];
        const char* listener_type_ptr = string_from_value(env,
                                                          listener_type_val);

        // TODO(tommymchugh): Figure out how to check for null for callback
        // Create async thread-safe callback function
        // Handle the threadsafe call by sending Notification into callback
        typedef napi_threadsafe_function_call_js ts_callback;
        ts_callback notification_cb = [](napi_env env,
                                         napi_value js_cb,
                                         void* context,
                                         void* data) {
            // Convert data to notification type
            SystemNotification* notif =
                reinterpret_cast<SystemNotification*>(data);

            // TODO(tommymchugh): determine proper context not undef
            napi_value undefined, notif_object;
            notification_to_object<SystemNotificationType>(env,
                                                           notif,
                                                           &notif_object);
            a_ok(napi_get_undefined(env, &undefined));
            a_ok(napi_call_function(env,
                                    undefined,
                                    js_cb,
                                    1, &notif_object,
                                    nullptr));
        };

        napi_value listener_callback_object = args[1];
        napi_threadsafe_function listener_callback;
        napi_value res_name;
        napi_create_string_utf8(env, "resource", NAPI_AUTO_LENGTH, &res_name);
        if (status != napi_ok) return nullptr;

        status = napi_create_threadsafe_function(env, listener_callback_object,
                                                 nullptr, res_name,
                                                 0, 2,
                                                 nullptr, nullptr, nullptr,
                                                 notification_cb,
                                                 &listener_callback);
        if (status != napi_ok) return nullptr;

        // Identify listener type
        if (!listener_type_ptr) {
            // TODO(tommymchugh): Implement catch all notification callback
            // ! Adds a callback function for all events
        } else {
            SystemNotificationType listener_type =
                SystemNotificationType::kUnknownSystemNotification;
            std::string type_str = std::string(listener_type_ptr);
            listener_type = string_to_notification_type(type_str);
            SystemNotificationManager* manager = sys_ptr->
                                                 GetNotificationManager();
            SystemNotificationCallback* callback =
                new SystemNotificationCallback([listener_callback]
                        (const SystemNotification* notification) {
                    napi_acquire_threadsafe_function(listener_callback);
                    napi_call_threadsafe_function(listener_callback,
                                                  (void*) notification,
                                                  napi_tsfn_blocking);
                });
            manager->AddEventListener(listener_type, callback);
        }
        delete listener_type_ptr;
        return nullptr;
    }, SystemInstance::GetInstance(), &add_event_listener);

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
void init(napi_env env, napi_value exports) {
    napi_status system_status = system(env, exports);
    if (system_status != napi_ok) {
        napi_throw_error(env,
                         nullptr,
                         "Failed to initialize environment/system");
        return;
    }

    napi_status notifications_status = notifications(env, exports);
    if (notifications_status != napi_ok) {
        napi_throw_error(env,
                         nullptr,
                         "Failed to initialize environment/notifications");
        return;
    }
}

}  // namespace environment
