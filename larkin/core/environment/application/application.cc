/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
