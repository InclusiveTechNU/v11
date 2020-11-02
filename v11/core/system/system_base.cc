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

#include "core/system/system_base.h"

namespace sys {

SystemBase::SystemBase() {
    running_apps_ = new absl::btree_set<Application*>();
}

void SystemBase::FreeRunningApplications() {
    if (!running_apps_) {
        return;
    }
    absl::btree_set<Application*>::iterator apps_iter = running_apps_->begin();
    while (apps_iter != running_apps_->end()) {
        delete (*apps_iter);
        running_apps_->erase(apps_iter);
        apps_iter++;
    }
}

void SystemBase::AddApplicationChangeListener() {
    SystemNotificationType launch_type = SystemNotificationType::kApplicationDidLaunch;
    SystemNotificationType exit_type = SystemNotificationType::kApplicationDidTerminate;
    SystemNotificationCallback* launch_cb = new SystemNotificationCallback(
                                        [&](const SystemNotification* notif) {
        std::string data_key = std::string(kApplicationDataTypeKey);
        const NotificationData* data = notif->GetData(data_key);
        if (!data) {
            return;
        }
        const Application* app = (const Application*) data->GetData();
        Application* app_instance = new Application(app->get_process_id());
        running_apps_->insert(app_instance);
    });
    SystemNotificationCallback* exit_cb = new SystemNotificationCallback(
                                        [&](const SystemNotification* notif) {
        std::string data_key = std::string(kProcessIdentifierDataTypeKey);
        const NotificationData* data = notif->GetData(data_key);
        if (!data) {
            return;
        }
        const pid_t* process_id = (const pid_t*) data->GetData();
        absl::btree_set<Application*>::iterator apps_iter = running_apps_->begin();
        while (apps_iter != running_apps_->end()) {
            Application* app = (*apps_iter);
            const pid_t app_pid = app->get_process_id();
            if (app_pid == (*process_id)) {
                delete app;
                running_apps_->erase(apps_iter);
                break;
            }
            apps_iter++;
        }
    });
    notification_manager_->AddEventListener(launch_type, launch_cb);
    notification_manager_->AddEventListener(exit_type, exit_cb);
}

const Platform* SystemBase::GetPlatform() const {
    return platform_;
}

SystemNotificationManager* const SystemBase::GetNotificationManager() const {
    return notification_manager_;
}

const absl::btree_set<Application*>* SystemBase::GetRunningApplications() const {
    return running_apps_;
}

SystemBase::~SystemBase() {
    FreeRunningApplications();
    delete platform_;
    delete notification_manager_;
    delete running_apps_;
}

}  // namespace sys
