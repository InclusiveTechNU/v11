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
#include "larkin/runtime/node/utils.h"
#include "utils/run_main.h"

using utils::create_main_app;
using utils::send_event;

namespace utils {

char* string_from_value(napi_env env, napi_value value) {
    size_t value_len = 0;
    size_t value_len_read = 0;
    char* text_buffer = nullptr;
    napi_get_value_string_utf8(env, value, nullptr, 0, &value_len);

    if (value_len != 0) {
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
    text_buffer = new char[1];
    text_buffer[0] = '\0';
    return text_buffer;
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

    napi_value process_id;
    a_ok(napi_create_string_utf8(env, std::to_string(application->get_process_id()).c_str(), NAPI_AUTO_LENGTH, &process_id));
    a_ok(napi_set_named_property(env, *value, "processId", process_id));

    if (application->get_bundle_id()) {
        napi_value bundle_value;
        a_ok(napi_create_string_utf8(env, application->get_bundle_id(), NAPI_AUTO_LENGTH, &bundle_value));
        a_ok(napi_set_named_property(env, *value, "id", bundle_value));
    }
}

void window_to_object(napi_env env,
                      AccessibilityWindow* window,
                      napi_value* value) {
    a_ok(napi_create_object(env, value));

    napi_value title_value;
    a_ok(napi_create_string_utf8(env, window->get_title(), NAPI_AUTO_LENGTH, &title_value));
    a_ok(napi_set_named_property(env, *value, "title", title_value));

    napi_value native_wrap_object;
    a_ok(napi_create_object(env, &native_wrap_object));
    a_ok(napi_wrap(env,
                   native_wrap_object,
                   (void*) window,
                   [](napi_env env, void* finalize_data, void* finalize_hint) {
                       delete (AccessibilityWindow*) finalize_data;
                   },
                   nullptr,
                   nullptr));
    a_ok(napi_set_named_property(env, *value, "native", native_wrap_object));
}

void element_to_object(napi_env env,
                       AccessibilityElement* element,
                       napi_value* value) {
    a_ok(napi_create_object(env, value));

    const char* type = element->get_type();
    const char* label = element->get_label();
    // TODO(tommymchugh): Initialize description value
    //const char* description = element->get_description();
    const char* value_str = element->get_value();
    const char* title = element->get_title();

    if (type) {
        napi_value type_value;
        a_ok(napi_create_string_utf8(env,
                                    type,
                                    NAPI_AUTO_LENGTH,
                                    &type_value));
        a_ok(napi_set_named_property(env, *value, "type", type_value));
    }

    if (label) {
        napi_value label_value;
        a_ok(napi_create_string_utf8(env,
                                    label,
                                    NAPI_AUTO_LENGTH,
                                    &label_value));
        a_ok(napi_set_named_property(env, *value, "label", label_value));
    }

    if (value_str) {
        napi_value value_value;
        a_ok(napi_create_string_utf8(env,
                                    value_str,
                                    NAPI_AUTO_LENGTH,
                                    &value_value));
        a_ok(napi_set_named_property(env, *value, "value", value_value));
    }

    if (title) {
        napi_value title_value;
        a_ok(napi_create_string_utf8(env,
                                    title,
                                    NAPI_AUTO_LENGTH,
                                    &title_value));
        a_ok(napi_set_named_property(env, *value, "title", title_value));
    }

    napi_value native_wrap_object;

    a_ok(napi_create_object(env, &native_wrap_object));
    a_ok(napi_wrap(env,
                   native_wrap_object,
                   (void*) element,
                   [](napi_env env, void* finalize_data, void* finalize_hint) {
                       delete (AccessibilityElement*) finalize_data;
                   },
                   nullptr,
                   nullptr));
    a_ok(napi_set_named_property(env, *value, "native", native_wrap_object));
}

void run_non_block_loop(uv_loop_t* node_loop) {
    create_main_app();
    while (true) {
        send_event();
        uv_run(node_loop, uv_run_mode::UV_RUN_NOWAIT);
    }
}
}  // namespace utils
