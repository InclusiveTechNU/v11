/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <vector>
#include <functional>
#include <string>
#include "environment/system/notifications/listener.h"
#include "environment/application/events.h"
#include "environment/application/application_info.h"
#include "environment/application/application_instance.h"
#include "environment/system/system.h"

using sys::notifications::callback;

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
    std::vector<ApplicationInstance *> instances;

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
    bool add_event_listener(app_event event,
                            callback callback);
};

};  // namespace app
