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

#include <stdint.h>
#include <string>
#include <map>
#include <utility>
#include "absl/container/flat_hash_set.h"
#include "runtime/node/utils.h"
#include "core/devices/keyboard/keycode.h"
#include "utils/run_main.h"

using utils::create_main_app;
using utils::send_event;
using sys::NotificationData;
using keyboard::keycode_to_uint;

namespace utils {

template <typename Type>
void notification_to_object(napi_env env,
                            const Notification<Type>* notification,
                            napi_value* value) {
    typedef std::map<std::string, std::string> notification_data;
    typedef std::pair<std::string, std::string> notification_pair;
    const absl::flat_hash_set<std::string>* data_keys = notification->
                                                        GetDataKeys();

    a_ok(napi_create_object(env, value));
    for (const std::string& key : *data_keys) {
        const NotificationData* data = notification->GetData(key);
        // TODO(tommymchugh): Support multiple types of data
        const std::string* data_str = (const std::string*) data;
        std::string data_cpy = std::string(*data_str);

        napi_value key_prop, value_prop;
        a_ok(napi_create_string_utf8(env,
                                     key.c_str(),
                                     NAPI_AUTO_LENGTH,
                                     &key_prop));
        a_ok(napi_create_string_utf8(env,
                                     data_cpy.c_str(),
                                     NAPI_AUTO_LENGTH,
                                     &value_prop));
        a_ok(napi_set_property(env, *value, key_prop, value_prop));
    }
}

}  // namespace utils
