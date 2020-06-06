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

#include "environment/application/application_instance.h"

using utils::error;
using utils::error_code;

namespace app {

ApplicationInstance::ApplicationInstance(pid_t pid,
                                         const running_app_update* data) {
    // TODO(tommymchugh): Support instantiating app using just pid
    process_id = new pid_t;
    *process_id = pid;
    if (data) {
        update_instance(*data);
    }
}

const char* ApplicationInstance::get_local_name() {
    if (!local_name)
        return nullptr;
    return local_name->c_str();
}

const char* ApplicationInstance::get_bundle_id() {
    if (!bundle_id)
        return nullptr;
    return bundle_id->c_str();
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

error ApplicationInstance::update_instance(const running_app_update& update) {
    if (terminated) {
        return {true, error_code::ERROR_FAILED_LINKING_MANAGER_BRIDGE};
    }

    delete local_name;
    local_name = new std::string(update.local_name);

    delete bundle_id;
    bundle_id = new std::string(update.bundle_id);

    delete fully_launched;
    fully_launched = new bool;
    *fully_launched = update.fully_launched;

    delete visibility;
    visibility = new app::visibility;
    *visibility = update.visibility;

    terminated = update.terminated;
    return {false, error_code::ERROR_CODE_NONE};
}

void ApplicationInstance::terminate_instance() {
    terminated = true;

    delete local_name;
    local_name = nullptr;

    delete bundle_id;
    bundle_id = nullptr;

    delete process_id;
    process_id = nullptr;

    delete fully_launched;
    fully_launched = nullptr;

    delete visibility;
    visibility = nullptr;

    delete linked_to_app;
    linked_to_app = nullptr;
}

ApplicationInstance::~ApplicationInstance() {
    terminate_instance();
}

};  // namespace app
