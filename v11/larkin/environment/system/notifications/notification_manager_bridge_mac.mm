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

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <map>
#include <iostream>
#include <string>
#include "utils/definitions.h"
#include "utils/string.h"
#include "larkin/environment/system/notifications/notification.h"
#include "larkin/environment/system/notifications/notification_manager_bridge.h"

#define A11Y_CHANGE NSWorkspaceAccessibilityDisplayOptionsDidChangeNotification

// Native list of supported notification types
#define SUPPORTED_NN @[NSWorkspaceDidLaunchApplicationNotification, \
                       NSWorkspaceDidTerminateApplicationNotification, \
                       NSWorkspaceDidHideApplicationNotification, \
                       NSWorkspaceDidUnhideApplicationNotification, \
                       NSWorkspaceDidMountNotification, \
                       NSWorkspaceDidUnmountNotification, \
                       NSWorkspaceDidWakeNotification, \
                       NSWorkspaceWillPowerOffNotification, \
                       NSWorkspaceWillSleepNotification, \
                       A11Y_CHANGE]
using utils::error;
using utils::error_code;
using utils::string_copy;

namespace sys {

NotificationManagerBridge* NotificationManagerBridge::
                           create_bridge(const manager_type& type) {
    native_manager system_center = nullptr;

    if (type == system) {
        NSNotificationCenter* native_system_center = [[NSWorkspace
                                                       sharedWorkspace]
                                                       notificationCenter];
        system_center = (__bridge_retained native_manager)
                        native_system_center;
    } else if (type == custom) {
        // TODO(tommymchugh): This will not happen often should we support?
    }

    if (!system_center)
        return nullptr;

    return new NotificationManagerBridge(system_center, type);
}

NotificationManagerBridge::
NotificationManagerBridge(native_manager manager,
                          manager_type type) :
                          notification_manager(manager),
                          nm_type(type) {  }

error NotificationManagerBridge::register_global_observer(const global_observer
                                                                observer) {
    NSNotificationCenter* nm_center = (__bridge NSNotificationCenter*)
                                      notification_manager;

    // TODO(tommymchugh): Couldn't figure out how to do a catch all for this
    // so just looping
    NSArray *notifications_observing = SUPPORTED_NN;

    for (int i = 0; i < [notifications_observing count]; i++) {
        NSNotificationName notification_type = notifications_observing[i];
        [nm_center 
            addObserverForName:notification_type
            object: nil
            queue: nil
            usingBlock: ^(NSNotification *native_notification){
                // Create a notification
                NSNotificationName native_name = [native_notification name];
                const char* native_name_raw = [native_name UTF8String];

                enum notification_type nn_value = UNKNOWN;
                if (native_name ==
                    NSWorkspaceDidLaunchApplicationNotification) {
                    nn_value = APPLICATION_DID_LAUNCH;
                } else if (native_name ==
                           NSWorkspaceDidTerminateApplicationNotification) {
                    nn_value = APPLICATION_DID_TERMINATE;
                } else if (native_name ==
                           NSWorkspaceDidHideApplicationNotification) {
                    nn_value = APPLICATION_DID_HIDE;
                } else if (native_name ==
                           NSWorkspaceDidUnhideApplicationNotification) {
                    nn_value = APPLICATION_DID_UNHIDE;
                } else if (native_name == NSWorkspaceDidMountNotification) {
                    nn_value = DEVICE_DID_MOUNT;
                } else if (native_name == NSWorkspaceDidUnmountNotification) {
                    nn_value = DEVICE_DID_UNMOUNT;
                } else if (native_name == NSWorkspaceDidWakeNotification) {
                    nn_value = SYSTEM_DID_WAKE;
                } else if (native_name ==
                           NSWorkspaceWillPowerOffNotification) {
                    nn_value = SYSTEM_WILL_POWER_OFF;
                } else if (native_name == NSWorkspaceWillSleepNotification) {
                    nn_value = SYSTEM_DID_SLEEP;
                } else if (native_name == A11Y_CHANGE) {
                    nn_value = ACCESSIBILITY_DID_CHANGE;
                }

                Notification* sys_notification = 
                                new Notification(native_name_raw,
                                                 nn_value);

                if (nn_value == APPLICATION_DID_LAUNCH ||
                    nn_value == APPLICATION_DID_TERMINATE ||
                    nn_value == APPLICATION_DID_HIDE ||
                    nn_value == APPLICATION_DID_UNHIDE) {
                    // TODO(tommymchugh): Handle application logic from environment/application
                    /*
                    NSDictionary* notification_data = [native_notification userInfo];
                    // TODO(tommymchugh): Turn this application into larkin app instance
                    NSRunningApplication* native_app = notification_data[@"NSWorkspaceApplicationKey"];
                    Application* app = new Application([native_app processIdentifier]);
                    // TODO(tommymchugh): Add all application instance objects to map
                    sys_notification->put_data_with_key("processId", std::to_string(app->get_process_id()));
                    if (app->get_bundle_id() != nullptr) {
                        sys_notification->put_data_with_key("id", std::string(app->get_bundle_id()));
                    }
                    if (app->get_name() != nullptr) {
                        sys_notification->put_data_with_key("name", std::string(app->get_name()));
                    }
                    delete app;*/
                }

                // Push the notification to the global observer
                observer(sys_notification);
            }];
    }
    registered_global_observer = true;
    return {false, error_code::ERROR_CODE_NONE};
}

/* !! See header for reference on why this is still here !!
void NotificationManagerBridge::remove_global_observer() {
    NSArray *notifications_observing = SUPPORTED_NN;
    NSNotificationCenter* nm_center = (__bridge NSNotificationCenter*)
                                      notification_manager;
    for (int i = 0; i < [notifications_observing count]; i++) {
        NSNotificationName notification_type = notifications_observing[i];
        [nm_center addObserverForName:notification_type
                   object: nil
                   queue: nil
                   usingBlock: ^(NSNotification *native_notification){  }
    }
} */

void NotificationManagerBridge::post_notification(const Notification
                                                        notification) {

}

NotificationManagerBridge::~NotificationManagerBridge() {
    // Release the notification manager to ARC
    if (notification_manager) {
        __lk_unused__ (__bridge_transfer NSNotificationCenter*)
                   notification_manager;
    }
}

}  // namespace sys
