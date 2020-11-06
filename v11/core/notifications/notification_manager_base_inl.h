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
#include <utility>
#include "core/notifications/notification_manager_base.h"

namespace sys {

template <typename Type>
NotificationManagerBase<Type>::NotificationManagerBase() {
    listeners_ = new absl::flat_hash_map<Type,
                                         NotificationCallback<Type>*>;
}

template <typename Type>
const std::vector<InputSource<Type>*>* NotificationManagerBase<Type>::
                                 GetInputSources() const {
    return &sources_;
}

template <typename Type>
void NotificationManagerBase<Type>::
     AddEventListener(Type type, NotificationCallback<Type>* callback) {
    auto present_callback = listeners_->find(type);
    if (present_callback != listeners_->end()) {
        delete present_callback->second;
    }
    (*listeners_)[type] = callback;
}

template <typename Type>
NotificationManagerBase<Type>::~NotificationManagerBase() {
    for (std::pair<Type,
                   NotificationCallback<Type>*> listener : *listeners_) {
        delete listener.second;
    }
    delete listeners_;
}

}  // namespace sys
