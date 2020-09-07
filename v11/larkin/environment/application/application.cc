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

#include "larkin/environment/application/application.h"

namespace app {

ApplicationObserver* Application::get_observer() {
    if (!_observer) {
        _observer = ApplicationObserver::create_observer(get_process_id());
    }
    return _observer;
}

const char* Application::get_name() const {
    if (_local_name) {
        return _local_name->c_str();
    }
    return nullptr;
}

const char* Application::get_bundle_id() const {
    if (_bundle_id) {
        return _bundle_id->c_str();
    }
    return nullptr;
}

pid_t Application::get_process_id() const {
    return _process_id;
}

Application::~Application() {
    delete _observer;
    delete _local_name;
    delete _bundle_id;
}

};  // namespace app
