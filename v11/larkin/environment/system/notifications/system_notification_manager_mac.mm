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

#include "larkin/environment/system/notifications/system_notification_manager_mac.h"
#include "larkin/environment/system/notifications/input_source.h"
#include "larkin/environment/system/notifications/notification_manager_base.h"
#include "larkin/environment/system/notifications/workspace_input_source_mac.h"

namespace sys {

SystemNotificationManagerMac::SystemNotificationManagerMac() :
                              SystemNotificationManager() {
    AttachInputSources();
}

void SystemNotificationManagerMac::AttachInputSources() {
    sources_.push_back(new WorkspaceInputSourceMac());
    for (InputSource* source : sources_) {
        source->SetCallback(new InputSourceCallback([&](const Notification*
                                                        notification) {
            auto present_callback = listeners_->find(notification->GetType());
            if (present_callback != listeners_->end()) {
                (*present_callback->second)(notification);
            }
        }));
    }
}

}  // namespace sys