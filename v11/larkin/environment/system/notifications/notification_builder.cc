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

#include "larkin/environment/system/notifications/notification_builder.h"

namespace sys {

NotificationBuilder::NotificationBuilder() {
    data_ = new absl::flat_hash_map<std::string, NotificationData*>;
    keys_ = new absl::flat_hash_set<std::string>;
}

NotificationBuilder::~NotificationBuilder() {
    FreeStoredData();
    delete data_;
    delete keys_;
}

void NotificationBuilder::FreeStoredData() {
    if (!data_) {
        return;
    }
    absl::flat_hash_map<std::string,
                        NotificationData*>::iterator data_iter = data_->begin();
    while (data_iter != data_->end()) {
        delete data_iter->second;
        data_->erase(data_iter);
        data_iter++;
    }
}

NotificationBuilder* NotificationBuilder::Create() {
    return new NotificationBuilder;
}

Notification* NotificationBuilder::Build() {
    return this;
}

const absl::flat_hash_map<std::string, NotificationData*>*
      NotificationBuilder::GetDataMap() const {
    return data_;
}

const absl::flat_hash_set<std::string>* NotificationBuilder::
                                        GetDataKeys() const {
    return keys_;
}

void NotificationBuilder::
    PutData(const std::string& key, NotificationData* value) {
    data_->insert({key, value});
    keys_->insert({key});
}

const NotificationData* NotificationBuilder::
                        GetData(const std::string& key) const {
    auto key_result = data_->find(key);
    if (key_result == data_->end()) {
        return nullptr;
    }
    return key_result->second;
}

void NotificationBuilder::SetType(NotificationType type) {
    type_ = type;
}

NotificationType NotificationBuilder::GetType() const {
    return type_;
}

}  // namespace sys
