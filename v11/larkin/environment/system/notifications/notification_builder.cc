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
namespace notifications {

NotificationBuilder::NotificationBuilder() {
    data_ = new absl::flat_hash_map<std::string, int>;
    keys_ = new absl::flat_hash_set<std::string>;
}

NotificationBuilder::~NotificationBuilder() {
    delete data_;
    delete keys_;
}

NotificationBuilder* NotificationBuilder::Create() {
    return new NotificationBuilder;
}

const Notification* NotificationBuilder::Build() {
    return this;
}

const absl::flat_hash_map<std::string, int>* NotificationBuilder::GetDataMap() const {
    return data_;
}

const absl::flat_hash_set<std::string>* NotificationBuilder::GetDataKeys() const {
    return keys_
}

void NotificationBuilder::PutData(const std::string& key, int value) {
    data_->insert({key, value});
    keys_->insert({key});
}

int NotificationBuilder::GetData(const std::string& key) const {
    auto key_result = data_->find(key);
    if (key_result == data_->end()) {
        return -1;
    }
    return key_result->second;
}

void NotificationBuilder::SetType(notification_type type) {
    type_ = type;
}

notification_type NotificationBuilder::GetType() const {
    return type_;
}

void NotificationBuilder::SetManager(const NotificationManager* manager) {
    manager_ = manager;
}

const NotificationManager* NotificationBuilder::GetManager() const {
    return manager_;
}

}  // namespace notifications
}  // namespace sys
