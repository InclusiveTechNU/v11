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

#include <functional>
#include "core/notifications/notification_manager_builder.h"

namespace sys {

template <typename Type>
NotificationManagerBuilder<Type>* NotificationManagerBuilder<Type>::Create() {
    return new NotificationManagerBuilder<Type>;
}

template <typename Type>
NotificationManager<Type>* NotificationManagerBuilder<Type>::Build() {
    return this;
}

template <typename Type>
ManagerType NotificationManagerBuilder<Type>::GetManagerType() const {
    return type_;
}

template <typename Type>
void NotificationManagerBuilder<Type>::AttachInputSource(InputSource<Type>* source) {
    sources_.push_back(source);
    source->SetCallback(new InputSourceCallback<Type>([&](const Notification<Type>*
                                                          notification) {
        auto present_callback = listeners_->find(notification->GetType());
        if (present_callback != listeners_->end()) {
            (*present_callback->second)(notification);
        }
    }));
}

}  // namespace sys
