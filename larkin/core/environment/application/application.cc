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

#include <string.h>
#include <stdexcept>
#include "utils/definitions.h"
#include "environment/application/application.h"

namespace app {

Application::Application(app_id id) {
    if (id.type == app::bundle_id) {
        bundle_id = std::string(id.id);
    } else {
        // TODO(tommymchugh): Support file path application instantiation
        char error_msg[] = "File path application cannot be instantiated";
        throw std::runtime_error(error_msg);
    }

    // Retrieve current running applications
    ApplicationInstance::get_system_instances(bundle_id, this, instances);

    if (instances.size() > 0) {
        launched = true;
        local_name = std::string(instances[0]->get_local_name());
    }
}

sys::System* Application::get_system() {
    return system;
}

app_info Application::get_app_info() {
    return {local_name.c_str(), bundle_id.c_str()};
}

Application::~Application() {
    for (int i = 0; i < instances.size(); i++) {
        delete instances[i];
    }

    delete instances;
}

};  // namespace app
