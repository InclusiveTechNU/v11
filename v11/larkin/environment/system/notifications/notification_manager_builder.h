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

#pragma once

#include <vector>
#include "absl/container/flat_hash_map.h"
#include "larkin/environment/system/notifications/notification_manager.h"
#include "larkin/environment/system/notifications/notification.h"
#include "larkin/environment/system/notifications/input_source.h"

namespace sys {

class NotificationManagerBuilder : public NotificationManager {
 private:
    NotificationManagerBuilder();
    // TODO(tommymchugh): Determine whether managers own input sources
    std::vector<InputSource*> sources_;
    absl::flat_hash_map<NotificationType,
                        NotificationCallback*>* listeners_ = nullptr;
    ManagerType type_ = ManagerType::kCustom;

 public:
    ~NotificationManagerBuilder();
    static NotificationManagerBuilder* Create();
    NotificationManager* Build();
    void AttachInputSource(InputSource* source);

    // From NotificationManager class
    const std::vector<InputSource*>* GetInputSources() const;
    ManagerType GetManagerType() const;
    void AddEventListener(NotificationType type,
                          NotificationCallback* callback);
};

}  // namespace sys
