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

#include <stdint.h>
#include <string>
#include <map>
#include <utility>
#include <iostream>
#include "absl/container/flat_hash_set.h"
#include "runtime/node/utils.h"
#include "core/devices/keyboard/keycode.h"
#include "utils/run_main.h"

using utils::create_main_app;
using utils::send_event;
using sys::NotificationData;
using keyboard::keycode_to_uint;

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

void application_to_object(napi_env env,
                           const Application* application,
                           napi_value* value) {
    a_ok(napi_create_object(env, value));

    if (application->get_name()) {
        napi_value name_value;
        a_ok(napi_create_string_utf8(env,
                                     application->get_name(),
                                     NAPI_AUTO_LENGTH,
                                     &name_value));
        a_ok(napi_set_named_property(env, *value, "name", name_value));
    }

    napi_value process_id;
    pid_t raw_pid = application->get_process_id();
    std::string pid_str = std::to_string(raw_pid);
    a_ok(napi_create_string_utf8(env,
                                 pid_str.c_str(),
                                 NAPI_AUTO_LENGTH,
                                 &process_id));
    a_ok(napi_set_named_property(env, *value, "processId", process_id));

    if (application->get_bundle_id()) {
        napi_value bundle_value;
        a_ok(napi_create_string_utf8(env,
                                     application->get_bundle_id(),
                                     NAPI_AUTO_LENGTH,
                                     &bundle_value));
        a_ok(napi_set_named_property(env, *value, "id", bundle_value));
    }
}

void window_to_object(napi_env env,
                      AccessibilityWindow* window,
                      napi_value* value) {
    a_ok(napi_create_object(env, value));

    napi_value title_value;
    a_ok(napi_create_string_utf8(env,
                                 window->get_title(),
                                 NAPI_AUTO_LENGTH,
                                 &title_value));
    a_ok(napi_set_named_property(env, *value, "title", title_value));

    napi_value native_wrap_object;
    a_ok(napi_create_object(env, &native_wrap_object));
    a_ok(napi_wrap(env,
                   native_wrap_object,
                   reinterpret_cast<void*>(window),
                   [](napi_env env, void* data, void* hint) {
                        delete reinterpret_cast<AccessibilityWindow*>(data);
                   },
                   nullptr,
                   nullptr));
    a_ok(napi_set_named_property(env, *value, "native", native_wrap_object));
}

void keyboard_event_to_object(napi_env env,
                      KeyboardEvent* event,
                      napi_value* value) {
    a_ok(napi_create_object(env, value));

    napi_value type_value, key_value;
    std::string type_str;
    if (event->get_event_type() == event_type::KEY_DOWN) {
        type_str = "press";
    } else {
        type_str = "release";
    }
    uint32_t code = keycode_to_uint(event->get_event_target_key());
    a_ok(napi_create_string_utf8(env,
                                 type_str.c_str(),
                                 NAPI_AUTO_LENGTH,
                                 &type_value));
    a_ok(napi_create_int32(env, code, &key_value));
    a_ok(napi_set_named_property(env, *value, "type", type_value));
    a_ok(napi_set_named_property(env, *value, "key", key_value));
}

void element_to_object(napi_env env,
                       AccessibilityElement* element,
                       napi_value* value) {
    a_ok(napi_create_object(env, value));

    const char* type = element->get_type();
    const char* label = element->get_label();
    // TODO(tommymchugh): Initialize description value
    // const char* description = element->get_description();
    const char* value_str = element->get_value();
    const char* title = element->get_title();
    const char* help_text = element->get_help_text();

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

    if (help_text) {
        napi_value help_text_value;
        a_ok(napi_create_string_utf8(env,
                                    help_text,
                                    NAPI_AUTO_LENGTH,
                                    &help_text_value));
        a_ok(napi_set_named_property(env, *value, "helpText", help_text_value));
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
                   reinterpret_cast<void*>(element),
                   [](napi_env env, void* data, void* hint) {
                       delete reinterpret_cast<AccessibilityElement*>(data);
                   },
                   nullptr,
                   nullptr));
    a_ok(napi_set_named_property(env, *value, "native", native_wrap_object));
}

void run_non_block_loop(uv_loop_t* node_loop) {
    int timeout_length = uv_backend_timeout(node_loop);
    send_event(timeout_length);
}
}  // namespace utils
