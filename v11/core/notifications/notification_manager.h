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
#include "core/notifications/notification.h"
#include "core/notifications/input_source.h"

namespace sys {

// TODO(tommymchugh): I'm not sure about whether this should be
// events instead of notifications so that we can have notifications
// be for actual popup alert notifications.

// Listener callback function that is called when
// event is triggered. Returns the notification that was observed.
// ! After performing callback on notification it is released
template <typename Type>
using NotificationCallback = InputSourceCallback<Type>;

// Notification managers can support a default
// system manager type or a custom type for group
// specific types of system notifications.
//    `system`: default system manager type
//    `custom`: a custom notification grouping
enum ManagerType {
    kSystem,
    kCustom
};

template <typename Type>
class NotificationManager {
 public:
    virtual ~NotificationManager() {}
    virtual const std::vector<InputSource<Type>*>* GetInputSources() const = 0;
    virtual ManagerType GetManagerType() const = 0;
    virtual void AddEventListener(Type type,
                                  NotificationCallback<Type>* callback) = 0;
};

}  // namespace sys
