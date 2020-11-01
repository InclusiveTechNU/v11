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

#include "larkin/environment/system/notifications/notification_manager_base.h"
#include "larkin/environment/system/notifications/input_source.h"

namespace sys {

template <typename Type>
class NotificationManagerBuilder : public NotificationManagerBase<Type> {
 private:
    using NotificationManagerBase<Type>::NotificationManagerBase;
    ManagerType type_ = ManagerType::kCustom;

 public:
    static NotificationManagerBuilder<Type>* Create();
    NotificationManager<Type>* Build();
    void AttachInputSource(InputSource<Type>* source);

    // From NotificationManagerBase class
    ManagerType GetManagerType() const;
};

}  // namespace sys

#include "larkin/environment/system/notifications/notification_manager_base_inl.h"
