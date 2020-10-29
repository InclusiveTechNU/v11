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
#include "larkin/environment/system/system_mac.h"
#include "larkin/environment/system/notifications/system_notification_manager_mac.h"
#include "larkin/environment/system/platform/platform_mac.h"
#include "larkin/environment/system/notifications/notification.h"
#include "larkin/environment/system/notifications/notification_manager.h"

namespace sys {

SystemMac::SystemMac() : SystemBase() {
    notification_manager_ = new SystemNotificationManagerMac();
    platform_ = new PlatformMac();
    LoadRunningApplications();
    AddApplicationChangeListener();
}

void SystemMac::LoadRunningApplications() {
    NSArray<NSRunningApplication*>* apps = [[NSWorkspace sharedWorkspace]
                                                         runningApplications];
    for (NSRunningApplication* app : apps) {
        pid_t process_id = app.processIdentifier;
        Application* app_instance = new Application(process_id);
        running_apps_->insert(app_instance);
    }
}

const void* SystemMac::GetRunningScreenReader() const {
    // TODO(tommymchugh): Manage voiceover screenreader interface
    return nullptr;
}

void SystemMac::StartApplicationNamed(const std::string& name) const {

}

void SystemMac::StartApplicationAtPath(const std::string& path) const {
    NSString* path_str = [NSString stringWithUTF8String: path.c_str()];
    NSURL* path_url = [NSURL fileURLWithPath: path_str];
    NSWorkspaceOpenConfiguration* config = [NSWorkspaceOpenConfiguration configuration];
    [[NSWorkspace sharedWorkspace] openApplicationAtURL: path_url
                                   configuration: config
                                   completionHandler: nil];
}

void SystemMac::HideOtherApplications() const {
    [[NSWorkspace sharedWorkspace] hideOtherApplications];
}

SystemMac::~SystemMac() { }

}  // namespace sys
