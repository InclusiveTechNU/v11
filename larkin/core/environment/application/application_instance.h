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

//    `pid`: The process id (or null if not running) of the app instance.
//    `launched`: Whether the application is fully finished launching.
//    `visibility`: The current visibility of the application.
//    `terminated`: Whether the process of the application has been terminated.

#pragma once

#include <sys/types.h>
#include <string>
#include <vector>
#include "utils/error.h"
#include "environment/system/notifications/listener.h"
#include "environment/application/application_info.h"

using utils::error;
using sys::notifications::callback;

namespace app {

// TODO(tommymchugh): ApplicationInstance is a bad identifier.
// replace with Instance

// A structure of data to update a
// running application instance.
struct running_app_update {
    const std::string local_name;
    const std::string bundle_id;
    const int architecture;
    const bool fully_launched;
    const visibility visibility;
    const bool terminated;
};

class ApplicationInstance {
 private:
    // The localized name of the application
    std::string* local_name = nullptr;

    // The bundle identifier of the application
    std::string* bundle_id = nullptr;

    // The process id of the running app instance.
    // Process id cannot be updated but will be null when instance
    // is terminated.
    pid_t* process_id = nullptr;

    // Whether the application is fully finished launching
    bool* fully_launched = nullptr;

    // The current visibility of the application instance
    visibility* visibility = nullptr;

    // Identifies whether an instance needs to be linked to a parent app
    bool* linked_to_app = nullptr;

    // Whether the running instance has been terminated
    bool terminated = false;

    // Updates the running application instance with new data
    error update_instance(const running_app_update& update);

    // Releases memory allocated from the current instance
    void terminate_instance();

    // Adds basic scaffolding for handling updates to the instance
    // when data from the system changes
    error register_event_listeners();

 public:
    // Adds all current system instances of the application to
    // the instances vector reference
    //static void get_system_instances(std::string bundle_id,
    //                                 Application* application,
    //                                 std::vector<ApplicationInstance *>&
    //                                             instances);

    // Transfers ownership of a running application process
    // using its process identifier. When `data` is not null
    // the application details are copied. Otherwise, the application
    // manager copies data and sets up update handlers.
    ApplicationInstance(pid_t pid, const running_app_update* data);

    explicit ApplicationInstance(void* native_app);

    // Deallocates all owned data about the application instance
    ~ApplicationInstance();

    // Get the localized name of the application transiently
    const char* get_local_name();

    // Get the bundle_id of the application transiently
    const char* get_bundle_id();

    // Returns a pointer to the process id (or null if not running).
    pid_t* get_process_id();

    // Returns whether the application is fully launched
    bool* is_launched();

    // Returns the visibility of the app instance
    app::visibility* get_visibility();

    // Returns whether the app instance has been terminated.
    // Terminated applications will also have null process_id pointers.
    bool is_terminated();

    // Applies a callback function `callback` whenever
    // an event `event` is called by the application
    // manager for this specific instance
    // bool add_event_listener(instance_event event,
    //                        callback callback);
};

};  // namespace app
