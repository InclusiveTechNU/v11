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
#include "core/system/notifications/workspace_input_source_mac.h"
#include "core/applications/application.h"
#include "core/notifications/notification.h"
#include "core/notifications/notification_builder.h"
#include "core/notifications/notification_data_builder.h"

using app::Application;

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

const SystemNotificationType kCoreNotificationTypes[] = {
    SystemNotificationType::kApplicationDidLaunch,
    SystemNotificationType::kApplicationDidTerminate,
    SystemNotificationType::kApplicationDidHide,
    SystemNotificationType::kApplicationDidUnhide,
    SystemNotificationType::kDeviceDidMount,
    SystemNotificationType::kDeviceDidUnmount,
    SystemNotificationType::kSystemDidWake,
    SystemNotificationType::kSystemWillPowerOff,
    SystemNotificationType::kSystemDidSleep,
    SystemNotificationType::kAccessibilityDidChange,
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
            NotificationBuilder<SystemNotificationType>* notif_builder = NotificationBuilder<SystemNotificationType>::Create();
            NSNotificationName native_name = [native_notification name];
            SystemNotificationType notification_type = SystemNotificationType::kUnknownSystemNotification;
            for (int i = 0; i < [kNativeNotificationTypes count]; i++) {
                if (native_name == kNativeNotificationTypes[i]) {
                    notification_type = kCoreNotificationTypes[i];
                    break;
                }
            }
            notif_builder->SetType(notification_type);

            if (notification_type == kApplicationDidLaunch ||
                notification_type == kApplicationDidHide ||
                notification_type == kApplicationDidUnhide) {
                NotificationDataBuilder* data_builder = NotificationDataBuilder::Create();
                NSDictionary* notification_data = [native_notification userInfo];
                NSRunningApplication* native_app = notification_data[@"NSWorkspaceApplicationKey"];
                Application* app = new Application([native_app processIdentifier]);
                data_builder->PutData(NotificationDataType::kApplicationType, (void*) app);
                NotificationData* app_data = data_builder->Build();
                notif_builder->PutData(std::string(kApplicationDataTypeKey),
                                       app_data);
            } else if (notification_type == kApplicationDidTerminate) {
                NotificationDataBuilder* data_builder = NotificationDataBuilder::Create();
                NSDictionary* notification_data = [native_notification userInfo];
                NSRunningApplication* native_app = notification_data[@"NSWorkspaceApplicationKey"];
                pid_t* process_id = new pid_t([native_app processIdentifier]);
                data_builder->PutData(NotificationDataType::kProcessIdentifierType,
                                      (void*) process_id);
                NotificationData* app_data = data_builder->Build();
                notif_builder->PutData(std::string(kProcessIdentifierDataTypeKey),
                                       app_data);
            }

            // Push the notification to the input source callback
            Notification<SystemNotificationType>* notification = notif_builder->Build();
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
