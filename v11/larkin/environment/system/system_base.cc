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

#include "larkin/environment/system/system_base.h"

namespace sys {

SystemBase::SystemBase() {
    runnings_apps_ = new absl::btree_set<Application*>();
}

void SystemBase::FreeRunningApplications() {
    if (!runnings_apps_) {
        return;
    }
    absl::btree_set<Application*>::iterator apps_iter = runnings_apps_->begin();
    while (apps_iter != runnings_apps_->end()) {
        delete (*apps_iter);
        runnings_apps_->erase(apps_iter);
        apps_iter++;
    }
}

const Platform* SystemBase::GetPlatform() const {
    return platform_;
}

NotificationManager* const SystemBase::GetNotificationManager() const {
    return notification_manager_;
}

const absl::btree_set<Application*>* SystemBase::GetRunningApplications() const {
    return runnings_apps_;
}

SystemBase::~SystemBase() {
    FreeRunningApplications();
    delete platform_;
    delete notification_manager_;
    delete runnings_apps_;
}

}  // namespace sys
