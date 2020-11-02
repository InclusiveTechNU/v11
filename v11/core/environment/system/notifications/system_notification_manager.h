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
#include "core/environment/system/notifications/system_notification.h"
#include "core/notifications/notification_manager.h"
#include "core/notifications/notification_manager_base.h"
#include "core/notifications/input_source.h"

namespace sys {

class SystemNotificationManager : public NotificationManagerBase
                                         <SystemNotificationType> {
 protected:
    SystemNotificationManager();
    ManagerType type_ = ManagerType::kSystem;
    virtual void AttachInputSources() = 0;

 public:
    virtual ~SystemNotificationManager();

    // From NotificationManager class
    ManagerType GetManagerType() const;
};

}  // namespace sys
