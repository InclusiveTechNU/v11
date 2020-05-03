/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <stdexcept>
#include "environment/application/application_instance.h"

using utils::error;

namespace app {

ApplicationInstance::ApplicationInstance(pid_t pid,
                                       const running_app_update* data) {
    // TODO(tommymchugh): Support instantiating app using just pid
    if (!data)
        throw std::runtime_error("App instances cannot be instantiated.");

    process_id = new pid_t;
    *process_id = pid;

    update_instance(*data);
}

const char* ApplicationInstance::get_local_name() {
    if (!local_name)
        return nullptr;
    return local_name->c_str();
}

pid_t* ApplicationInstance::get_process_id() {
    return process_id;
}

bool* ApplicationInstance::is_launched() {
    return fully_launched;
}

app::visibility* ApplicationInstance::get_visibility() {
    return visibility;
}

bool ApplicationInstance::is_terminated() {
    return terminated;
}

Application* ApplicationInstance::get_application() {
    return application;
}

error ApplicationInstance::update_instance(const running_app_update& update) {
    if (terminated) {
        const char error_msg[] = "Terminated instances cannot be linked.";
        return {true, error_msg};
    }

    delete local_name;
    if (!update.local_name) {
        local_name = nullptr;
    } else {
        local_name = new std::string;
        *local_name = std::string(update.local_name);
    }

    delete fully_launched;
    if (!fully_launched) {
        fully_launched = nullptr;
    } else {
        fully_launched = new bool;
        *fully_launched = update.fully_launched;
    }

    delete visibility;
    if (!visibility) {
        visibility = nullptr;
    } else {
        visibility = new app::visibility;
        *visibility = update.visibility;
    }

    if (!terminated && update.terminated) {
        terminate_instance();
    }

    return {false, nullptr};
}

void ApplicationInstance::terminate_instance() {
    terminated = true;

    delete local_name;
    local_name = nullptr;

    delete process_id;
    process_id = nullptr;

    delete fully_launched;
    fully_launched = nullptr;

    delete visibility;
    visibility = nullptr;

    delete linked_to_app;
    linked_to_app = nullptr;
}

error ApplicationInstance::link_application(Application* app) {
    if (terminated) {
        const char error_msg[] = "Terminated instances cannot be linked.";
        return {true, error_msg};
    }

    if (linked_to_app && *linked_to_app) {
        const char error_msg[] = "Existing application has already been linked";
        return {true, error_msg};
    }

    if (!app) {
        const char error_msg[] = "Linked application cannot be null";
        return {true, error_msg};
    }

    application = app;
    linked_to_app = new bool;
    *linked_to_app = true;

    return {false, nullptr};
}

ApplicationInstance::~ApplicationInstance() {
    terminate_instance();
}

};  // namespace app
