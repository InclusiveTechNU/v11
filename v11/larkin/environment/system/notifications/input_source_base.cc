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

#include "larkin/environment/system/notifications/input_source_base.h"

namespace sys {

InputSourceBase::~InputSourceBase() {
    ClearMemory();
    delete callback_;
}

void InputSourceBase::StoreNotification(Notification* notification) {
    if (IsStoringMemory()) {
        memory_.push_back(notification);
    } else {
        delete notification;
    }
}

void InputSourceBase::SetCallback(InputSourceCallback* callback) {
    callback_ = callback;
}

const InputSourceCallback* InputSourceBase::GetCallback() const {
    return callback_;
}

const InputSourceSettings& InputSourceBase::GetSettings() const {
    return settings_;
}

bool InputSourceBase::IsEnabled() const {
    return settings_.enabled;
}

void InputSourceBase::SetEnabled(bool enabled) {
    settings_.enabled = enabled;
}

void InputSourceBase::SetStoringMemory(bool storing) {
    settings_.store_memory = storing;
    if (!storing) {
        ClearMemory();
    }
}

bool InputSourceBase::IsStoringMemory() const {
    return settings_.store_memory;
}

void InputSourceBase::ClearMemory() {
    while (memory_.size() != 0) {
        delete memory_.back();
        memory_.pop_back();
    }
}

const std::vector<Notification*>* InputSourceBase::GetMemory() const {
    if (IsStoringMemory()) {
        return &memory_;
    }
    return nullptr;
}

const std::string& InputSourceBase::GetInputSourceName() const {
    return name_;
}

}  // namespace sys
