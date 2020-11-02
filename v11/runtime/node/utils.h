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

#include <assert.h>
#include <uv.h>
#include <node/node_api.h>
#include "core/notifications/notification.h"
#include "core/environment/application/application.h"
#include "core/accessibility/accessibility_window.h"
#include "core/accessibility/accessibility_element.h"
#include "core/interaction/keyboard/keyboard_event.h"

#define a_ok(call) assert(call == napi_ok)

using sys::Notification;
using app::Application;
using a11y::AccessibilityWindow;
using a11y::AccessibilityElement;
using keyboard::event::KeyboardEvent;
using keyboard::event::event_type;

namespace utils {

void keyboard_event_to_object(napi_env env,
                    KeyboardEvent* event,
                    napi_value* value);

char* string_from_value(napi_env env, napi_value value);

template <typename Type>
void notification_to_object(napi_env env,
                            const Notification<Type>* notification,
                            napi_value* value);

void application_to_object(napi_env env,
                           const Application* application,
                           napi_value* value);

void window_to_object(napi_env env,
                      AccessibilityWindow* window,
                      napi_value* value);

void element_to_object(napi_env env,
                       AccessibilityElement* element,
                       napi_value* value);

void run_non_block_loop(uv_loop_t* node_loop);

}  // namespace utils

#include "runtime/node/utils_inl.h"
