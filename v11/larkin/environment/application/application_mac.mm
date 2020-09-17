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
#include <vector>
#include <string>
#include "larkin/environment/application/application.h"

namespace app {

Application::Application(pid_t process_id) {
    NSRunningApplication* app = 
        [NSRunningApplication runningApplicationWithProcessIdentifier:
                              process_id];
    init_with_native((__bridge_retained void*) app);
}

Application::Application(const char* bundle_id) {
    // TODO(tommymchugh): Confirm only one bundle id is ok
    NSString* ns_bundle_id = [NSString stringWithUTF8String:bundle_id];
    NSRunningApplication* app = 
        [NSRunningApplication runningApplicationsWithBundleIdentifier:
                              ns_bundle_id][0];
    init_with_native((__bridge_retained void*) app);
}

void Application::init_with_native(void* native_app) {
    NSRunningApplication* app = (__bridge_transfer NSRunningApplication*)
                                native_app;
    _process_id = app.processIdentifier;
    if (app.bundleIdentifier != nil) {
        _bundle_id = new std::string([app.bundleIdentifier UTF8String]);
    }
    
    if (app.localizedName != nil) {
        _local_name = new std::string([app.localizedName UTF8String]);
    }
}

std::vector<Application*> Application::get_active_applications() {
    std::vector<Application*> active_apps_vec;
    NSArray<NSRunningApplication*>* active_apps = [[NSWorkspace
                                                    sharedWorkspace]
                                                    runningApplications];
    for (NSRunningApplication* running_app : active_apps) {
        Application* app = new Application(running_app.processIdentifier);
        active_apps_vec.push_back(app);
    }
    return active_apps_vec;
}

void Application::activate() {
    NSRunningApplication* app = 
        [NSRunningApplication runningApplicationWithProcessIdentifier:
                              _process_id];
    [app activateWithOptions:NSApplicationActivateIgnoringOtherApps];
}

}  // namespace app
