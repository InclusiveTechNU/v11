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

#pragma once

#include <vector>
#include <functional>
#include <string>
#include "environment/system/notifications/listener.h"
#include "environment/application/application_info.h"
#include "environment/application/application_instance.h"
#include "environment/system/system.h"

using sys::notifications::callback;
using app::ApplicationInstance;

namespace app {
class Application {
 private:
    // The bundle identifier of the application
    std::string bundle_id;

    // The localized name of the application
    std::string local_name;

    // Whether the application is fully launched
    bool launched = false;

    // A collection of all current instances of the application
    std::vector<ApplicationInstance*> instances;

    // Pointer to the main system manager
    sys::System* system = nullptr;

 public:
    // Creates applica tion state and details from
    // a bundle identifier.
    explicit Application(app_id id);
    ~Application();

    // Returns basic information about the application
    // in an app_info struct form. This app_info is constant
    // and will not change.
    app_info get_app_info();

    // Returns a collection of current running instances
    // of the application
    std::vector<ApplicationInstance> get_instances();

    // Returns a pointer to the main system manager for the
    // application
    sys::System* get_system();

    // Applies a callback function `callback` whenever
    // an event `event` is called by the application
    // manager.
    // bool add_event_listener(app_event event,
    //                        callback callback);
};

};  // namespace app
