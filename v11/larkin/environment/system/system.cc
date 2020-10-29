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

#include "larkin/environment/system/system.h"

namespace sys {

bool System::IsScreenReaderRunning() const {
    return GetRunningScreenReader() == nullptr;
}

bool System::IsApplicationRunning(const std::string& bundle_id) const {
    const absl::btree_set<Application*>* apps = GetRunningApplications();
    if (!apps) {
        return false;
    }

    absl::btree_set<Application*>::const_iterator apps_iter = apps->begin();
    while (apps_iter != apps->end()) {
        const Application* running_app = (*apps_iter);
        std::string app_bid = std::string(running_app->get_bundle_id());
        if (app_bid == bundle_id) {
            return true;
        }
        apps_iter++;
    }
    return false;
}

System::~System() { }

}  // namespace sys
