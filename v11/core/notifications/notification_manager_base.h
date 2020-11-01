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
#include "core/notifications/notification_manager.h"
#include "core/notifications/notification.h"
#include "core/notifications/input_source.h"

namespace sys {

template <typename Type>
class NotificationManagerBase : public NotificationManager<Type> {
 protected:
    NotificationManagerBase();
    // TODO(tommymchugh): Determine whether managers own input sources
    std::vector<InputSource<Type>*> sources_;
    absl::flat_hash_map<Type,
                        NotificationCallback<Type>*>* listeners_ = nullptr;

 public:
    virtual ~NotificationManagerBase();

    // From NotificationManager class
    virtual ManagerType GetManagerType() const = 0;
    const std::vector<InputSource<Type>*>* GetInputSources() const;
    void AddEventListener(Type type,
                          NotificationCallback<Type>* callback);
};

}  // namespace sys

#include "core/notifications/notification_manager_base_inl.h"
