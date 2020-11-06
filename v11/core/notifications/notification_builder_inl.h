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

#include <string>
#include "core/notifications/notification_builder.h"

namespace sys {

template <typename Type>
NotificationBuilder<Type>::NotificationBuilder() {
    data_ = new absl::flat_hash_map<std::string, NotificationData*>;
    keys_ = new absl::flat_hash_set<std::string>;
}

template <typename Type>
NotificationBuilder<Type>::~NotificationBuilder() {
    FreeStoredData();
    delete data_;
    delete keys_;
}

template <typename Type>
void NotificationBuilder<Type>::FreeStoredData() {
    if (!data_) {
        return;
    }
    absl::flat_hash_map<std::string, NotificationData*>::iterator data_iter =
        data_->begin();
    while (data_iter != data_->end()) {
        delete data_iter->second;
        data_->erase(data_iter);
        data_iter++;
    }
}

template <typename Type>
NotificationBuilder<Type>* NotificationBuilder<Type>::Create() {
    return new NotificationBuilder;
}

template <typename Type>
Notification<Type>* NotificationBuilder<Type>::Build() {
    return this;
}

template <typename Type>
const absl::flat_hash_map<std::string, NotificationData*>*
      NotificationBuilder<Type>::GetDataMap() const {
    return data_;
}

template <typename Type>
const absl::flat_hash_set<std::string>* NotificationBuilder<Type>::
                                        GetDataKeys() const {
    return keys_;
}

template <typename Type>
void NotificationBuilder<Type>::
    PutData(const std::string& key, NotificationData* value) {
    data_->insert({key, value});
    keys_->insert({key});
}

template <typename Type>
const NotificationData* NotificationBuilder<Type>::
                        GetData(const std::string& key) const {
    auto key_result = data_->find(key);
    if (key_result == data_->end()) {
        return nullptr;
    }
    return key_result->second;
}

template <typename Type>
void NotificationBuilder<Type>::SetType(Type type) {
    type_ = type;
}

template <typename Type>
Type NotificationBuilder<Type>::GetType() const {
    return type_;
}

}  // namespace sys
