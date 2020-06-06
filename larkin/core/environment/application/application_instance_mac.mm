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
#include <sys/types.h>
#include "utils/string.h"
#include "environment/application/application_instance.h"

namespace app {
    running_app_update create_instance_update(void* native_app) {
        NSRunningApplication* application = (__bridge_transfer NSRunningApplication*) native_app;
        // Push information to running_instance
        NSString* localized_name = [application localizedName];
        std::string local_name = std::string([localized_name UTF8String]);

        NSString* bundle_id_raw = [application bundleIdentifier];
        std::string bundle_id = std::string([bundle_id_raw UTF8String]);

        int architecture = [application executableArchitecture];
        bool launched = [application isFinishedLaunching] ? true : false;
        visibility app_visibility = [application isHidden] ? app::hidden : app::visible;
        bool terminated = [application isTerminated] ? true : false;

        return {
            local_name,         // local_name
            bundle_id,          // bundle_id
            architecture,       // architecture
            launched,           // fully_launched
            app_visibility,     // visibility
            terminated          // terminated
        };
    }

    ApplicationInstance::ApplicationInstance(void* native_app) {
        running_app_update app_info = create_instance_update(native_app);
        update_instance(app_info);
    }
};  // namespace app
