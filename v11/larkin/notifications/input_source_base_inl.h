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

#include "larkin/notifications/input_source_base.h"

namespace sys {

template <typename Type>
InputSourceBase<Type>::~InputSourceBase() {
    ClearMemory();
    delete callback_;
}

template <typename Type>
void InputSourceBase<Type>::StoreNotification(Notification<Type>* notification) {
    if (IsStoringMemory()) {
        memory_.push_back(notification);
    } else {
        delete notification;
    }
}

template <typename Type>
void InputSourceBase<Type>::SetCallback(InputSourceCallback<Type>* callback) {
    callback_ = callback;
}

template <typename Type>
const InputSourceCallback<Type>* InputSourceBase<Type>::GetCallback() const {
    return callback_;
}

template <typename Type>
const InputSourceSettings& InputSourceBase<Type>::GetSettings() const {
    return settings_;
}

template <typename Type>
bool InputSourceBase<Type>::IsEnabled() const {
    return settings_.enabled;
}

template <typename Type>
void InputSourceBase<Type>::SetEnabled(bool enabled) {
    settings_.enabled = enabled;
}

template <typename Type>
void InputSourceBase<Type>::SetStoringMemory(bool storing) {
    settings_.store_memory = storing;
    if (!storing) {
        ClearMemory();
    }
}

template <typename Type>
bool InputSourceBase<Type>::IsStoringMemory() const {
    return settings_.store_memory;
}

template <typename Type>
void InputSourceBase<Type>::ClearMemory() {
    while (memory_.size() != 0) {
        delete memory_.back();
        memory_.pop_back();
    }
}

template <typename Type>
const std::vector<Notification<Type>*>* InputSourceBase<Type>::GetMemory() const {
    if (IsStoringMemory()) {
        return &memory_;
    }
    return nullptr;
}

template <typename Type>
const std::string& InputSourceBase<Type>::GetInputSourceName() const {
    return name_;
}

}  // namespace sys
