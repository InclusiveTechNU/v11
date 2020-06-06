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
#include <vector>
#include "client/node/accessibility.h"
#include "client/node/utils.h"
#include "core/accessibility/accessibility_tree.h"
#include "core/accessibility/accessibility_element.h"

using utils::element_to_object;
using utils::window_to_object;
using a11y::AccessibilityWindow;
using a11y::AccessibilityTree;
using a11y::AccessibilityElement;

namespace a11y {

void windows(napi_env env, napi_value exports) {
    napi_value get_windows;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        napi_value windows_array;
        a_ok(napi_create_array(env, &windows_array));

        size_t args_count = 1;
        napi_value args[1];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value process_id_val = args[0];
        pid_t process_id;
        a_ok(napi_get_value_int32(env, process_id_val, &process_id));
        AccessibilityTree app_tree = AccessibilityTree(process_id);
        std::vector<AccessibilityWindow*> windows = app_tree.get_windows();

        for (int i = 0; i < windows.size(); i++) {
            AccessibilityWindow* window = windows[i];
            napi_value window_object;
            window_to_object(env, window, &window_object);
            a_ok(napi_set_element(env, windows_array, i, window_object));
        }
        return windows_array;
    }, nullptr, &get_windows));

    a_ok(napi_set_named_property(env,
                                 exports,
                                 "getWindows",
                                 get_windows));
}

void children(napi_env env, napi_value exports) {
    napi_value get_children;
    a_ok(napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        napi_value children_array;
        a_ok(napi_create_array(env, &children_array));

        size_t args_count = 1;
        napi_value args[1];
        a_ok(napi_get_cb_info(env, info, &args_count, args, nullptr, 0));

        napi_value native_wrapper = args[0];
        void* native_wrapper_ptr = nullptr;
        a_ok(napi_unwrap(env, native_wrapper, &native_wrapper_ptr));
        AccessibilityWindow* native_window =
            reinterpret_cast<AccessibilityWindow*>(native_wrapper_ptr);

        std::vector<AccessibilityElement*> children = native_window->
                                                      get_children();

        for (int i = 0; i < children.size(); i++) {
            AccessibilityElement* child = children[i];
            napi_value child_object;
            element_to_object(env, child, &child_object);
            a_ok(napi_set_element(env, children_array, i, child_object));
        }
        return children_array;
    }, nullptr, &get_children));
    a_ok(napi_set_named_property(env,
                                 exports,
                                 "getChildren",
                                 get_children));
}

// Initialize all variables and functions
void init(napi_env env, napi_value exports, System* sys_ptr) {
    napi_value accessibility_object;
    a_ok(napi_create_object(env, &accessibility_object));

    windows(env, accessibility_object);
    children(env, accessibility_object);

    a_ok(napi_set_named_property(env,
                                exports,
                                "accessibility",
                                accessibility_object));
}

};  // namespace environment
