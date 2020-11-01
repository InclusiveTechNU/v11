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
#include "larkin/environment/application/application.h"

using app::Application;

namespace sys {

SystemMac::SystemMac() : SystemBase() {
    notification_manager_ = new SystemNotificationManagerMac();
    platform_ = new PlatformMac();
    LoadRunningApplications();
    AddApplicationChangeListener();
}

std::string* SystemMac::GetApplicationPath(const std::string& name,
                                           const std::string& start_path) {
    NSString* app_name = [NSString stringWithUTF8String: name.c_str()];
    NSString* dir_path = [NSString stringWithUTF8String: start_path.c_str()];
    NSString* app_ext = [NSString stringWithUTF8String: kApplicationFileExt];
    NSString* encoded_file_name = [NSString stringWithFormat:@"%@%@",
                                            app_name,
                                            app_ext];
    NSFileManager* file_manager = [NSFileManager defaultManager];
    NSArray<NSString*>* dir_contents = [file_manager
                                        contentsOfDirectoryAtPath: dir_path
                                        error: nil];
    NSMutableArray<NSString*>* subdirs = [[NSMutableArray alloc] init];
    for (NSString* file_path : dir_contents) {
        if ([file_path isEqualToString: encoded_file_name]) {
            return new std::string(
                std::string([dir_path UTF8String]) +
                std::string(kNativeFileSeperator) +
                name +
                std::string(kApplicationFileExt)
            );
        } else {
            BOOL isDir = NO;
            BOOL exists = [file_manager fileExistsAtPath: dir_path
                                        isDirectory: &isDir];
            if ((exists && isDir) &&
                ![file_path hasSuffix: @".app"]) {
                NSString* sub_path = [NSString stringWithFormat:@"%@/%@",
                                                dir_path,
                                                file_path];
                [subdirs addObject: sub_path];
            }
        }
    }

     // Traverse application subdirectories since application path was
    // not yet found in standard application directories
    for (NSString* dir_path : subdirs) {
        std::string std_dir_path = std::string([dir_path UTF8String]);
        std::string* app_path = SystemMac::GetApplicationPath(name,
                                                              std_dir_path);
        if (app_path) {
            return app_path; 
        }
    }
    return nullptr;
}

SystemMac* SystemMac::GetInstance() {
    if (!instance_) {
        instance_ = new SystemMac();
    }
    return instance_;
}

void SystemMac::LoadRunningApplications() {
    NSArray<NSRunningApplication*>*
        apps = [[NSWorkspace sharedWorkspace] runningApplications];
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
    NSFileManager* file_manager = [NSFileManager defaultManager];
    NSSearchPathDirectory search_path = NSApplicationDirectory;
    NSSearchPathDomainMask search_domain = NSAllDomainsMask;
    NSArray<NSURL*>* app_dirs = [file_manager URLsForDirectory: search_path
                                              inDomains: search_domain];
    for (NSURL* app_dir : app_dirs) {
        NSString* dir_path = app_dir.path;
        BOOL isDir = NO;
        BOOL exists = [file_manager fileExistsAtPath: dir_path
                                    isDirectory: &isDir];
        if (exists && isDir) {
            std::string rel_path = std::string([dir_path UTF8String]);
            std::string* app_path = SystemMac::GetApplicationPath(name,
                                                                  rel_path);
            if (app_path) {
                StartApplicationAtPath(*app_path);
                delete app_path;
                return;
            }
            delete app_path;
        }
    }
    // TODO(tommymchugh): Throw rejection for not finding and
    // starting application
}

void SystemMac::StartApplicationAtPath(const std::string& path) const {
    NSString* path_str = [NSString stringWithUTF8String: path.c_str()];
    NSURL* path_url = [NSURL fileURLWithPath: path_str];
    NSWorkspaceOpenConfiguration* config = [NSWorkspaceOpenConfiguration
                                            configuration];
    [[NSWorkspace sharedWorkspace] openApplicationAtURL: path_url
                                   configuration: config
                                   completionHandler: nil];
}

void SystemMac::HideOtherApplications() const {
    [[NSWorkspace sharedWorkspace] hideOtherApplications];
}

SystemMac::~SystemMac() { }

}  // namespace sys
