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

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "client/node/utils.h"
#include "core/utils/run_main.h"

using utils::create_main_app;
using utils::send_event;

namespace utils {

char* string_from_value(napi_env env, napi_value value) {
    size_t value_len = -1;
    size_t value_len_read = -1;
    char* text_buffer = nullptr;
    napi_get_value_string_utf8(env, value, nullptr, 0, &value_len);

    if (value_len != -1) {
        text_buffer = new char[value_len+1];
        napi_status status;
        status = napi_get_value_string_utf8(env,
                                            value,
                                            text_buffer,
                                            value_len+1,
                                            &value_len_read);
        if (status != napi_ok) return nullptr;
        return text_buffer;
    }
    return nullptr;
}

void notification_to_object(napi_env env,
                            const Notification* notification,
                            napi_value* value) {
    typedef std::map<std::string, std::string> notification_data;
    typedef std::pair<std::string, std::string> notification_pair;
    notification_data data = notification->get_notification_data();

    a_ok(napi_create_object(env, value));
    for (notification_pair object : data) {
        napi_value key_prop, value_prop;
        a_ok(napi_create_string_utf8(env,
                                     object.first.c_str(),
                                     NAPI_AUTO_LENGTH,
                                     &key_prop));
        a_ok(napi_create_string_utf8(env,
                                     object.second.c_str(),
                                     NAPI_AUTO_LENGTH,
                                     &value_prop));
        a_ok(napi_set_property(env, *value, key_prop, value_prop));
    }
}

void application_to_object(napi_env env,
                           const Application* application,
                           napi_value* value) {
    a_ok(napi_create_object(env, value));

    if (application->get_name()) {
        napi_value name_value;
        a_ok(napi_create_string_utf8(env, application->get_name(), NAPI_AUTO_LENGTH, &name_value));
        a_ok(napi_set_named_property(env, *value, "name", name_value));
    }

    if (application->get_bundle_id()) {
        napi_value bundle_value;
        a_ok(napi_create_string_utf8(env, application->get_bundle_id(), NAPI_AUTO_LENGTH, &bundle_value));
        a_ok(napi_set_named_property(env, *value, "id", bundle_value));
    }
}

void window_to_object(napi_env env,
                      const AccessibilityWindow* window,
                      napi_value* value) {
    a_ok(napi_create_object(env, value));

    napi_value title_value;
    a_ok(napi_create_string_utf8(env, window->get_title(), NAPI_AUTO_LENGTH, &title_value));
    a_ok(napi_set_named_property(env, *value, "title", title_value));
}

void run_non_block_loop(uv_loop_t* node_loop) {
    create_main_app();
    while (true) {
        send_event();
        uv_run(node_loop, uv_run_mode::UV_RUN_NOWAIT);
    }
}
};  // namespace utils
