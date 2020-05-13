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
#include "environment/application/application_instance.h"

namespace app {
    void ApplicationInstance::get_system_instances(std::string bundle_id,
                                                   Application *application,
                                                   std::vector<ApplicationInstance*>&
                                                              instances) {
        NSString *bundle_id_str = [NSString stringWithUTF8String:bundle_id.c_str()];
        NSArray<NSApplicationInstance *> *running_instances = [ApplicationInstancesWithBundleIdentifier: bundle_id_str];

        for (int i = 0; i < [running_instances count]; i++) {
            NSApplicationInstance *running_instance_src = running_instances[i];
            pid_t process_id = [running_instance_src processIdentifier];

            ApplicationInstance *running_instance = new ApplicationInstance;
            running_instance = ApplicationInstance(process_id);
            running_instance->link_application(application);

            // Push information to running_instance
            std::string local_name = std::string([running_instance_src localizedName]);
            bool launched = [running_instance_src finishedLaunching];
            visibility app_visibility = [running_instance_src hidden] ? app::hidden : app::visible;
            bool terminated = [running_instance_src terminated] ? true : false;

            running_instance_update app_info = {
                local_name.c_str(),  // local_name
                launched,           // fully_launched
                app_visibility,     // visibility
                terminated          // terminated
            };

            running_instance->update_instance(app_info);
            running_instances->push_back(running_instance);
        }
    }
};  // namespace app
