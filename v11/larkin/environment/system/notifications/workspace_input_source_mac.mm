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

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include "larkin/environment/system/notifications/workspace_input_source_mac.h"
#include "larkin/environment/system/notifications/notification.h"
#include "larkin/environment/system/notifications/notification_builder.h"

namespace sys {

NSArray *const kNativeNotificationTypes = @[
    NSWorkspaceDidLaunchApplicationNotification,
    NSWorkspaceDidTerminateApplicationNotification,
    NSWorkspaceDidHideApplicationNotification,
    NSWorkspaceDidUnhideApplicationNotification,
    NSWorkspaceDidMountNotification,
    NSWorkspaceDidUnmountNotification,
    NSWorkspaceDidWakeNotification,
    NSWorkspaceWillPowerOffNotification,
    NSWorkspaceWillSleepNotification,
    NSWorkspaceAccessibilityDisplayOptionsDidChangeNotification
];

const NotificationType kLarkinNotificationTypes[] = {
    NotificationType::kApplicationDidLaunch,
    NotificationType::kApplicationDidTerminate,
    NotificationType::kApplicationDidHide,
    NotificationType::kApplicationDidUnhide,
    NotificationType::kDeviceDidMount,
    NotificationType::kDeviceDidUnmount,
    NotificationType::kSystemDidWake,
    NotificationType::kSystemWillPowerOff,
    NotificationType::kSystemDidSleep,
    NotificationType::kAccessibilityDidChange,
};

WorkspaceInputSourceMac::WorkspaceInputSourceMac() {
    NSWorkspace* shared_workspace = [NSWorkspace sharedWorkspace];
    NSNotificationCenter* ws_notifs = [shared_workspace notificationCenter];
    notification_center_ = (__bridge_retained void*) ws_notifs;
    RegisterNotificationObserver();
}

void WorkspaceInputSourceMac::RegisterNotificationObserver() {
    NSNotificationCenter* ws_notifs = (__bridge NSNotificationCenter*) notification_center_;
    for (NSNotificationName notification_name in kNativeNotificationTypes) {
        [ws_notifs addObserverForName:notification_name
                   object: nil
                   queue: nil
                   usingBlock: ^(NSNotification *native_notification){
            NotificationBuilder* notif_builder = NotificationBuilder::Create();
            NSNotificationName native_name = [native_notification name];
            NotificationType notification_type = NotificationType::kUnknown;
            for (int i = 0; i < [kNativeNotificationTypes count]; i++) {
                if (native_name == kNativeNotificationTypes[i]) {
                    notification_type = kLarkinNotificationTypes[i];
                    break;
                }
            }
            notif_builder->SetType(notification_type);

            /*if (notification_type == kApplicationDidLaunch ||
                notification_type == kApplicationDidTerminate ||
                notification_type == kApplicationDidHide ||
                notification_type == kApplicationDidUnhide) {
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
                delete app;
            }*/

            // Push the notification to the input source callback
            Notification* notification = notif_builder->Build();
            SendCallback(notification);
        }];
    }
}

const std::string& WorkspaceInputSourceMac::GetInputSourceName() const {
    return name_;
}

WorkspaceInputSourceMac::~WorkspaceInputSourceMac() {
    if (notification_center_) {
        CFRelease(notification_center_);
    }
}

}  // namespace sys
