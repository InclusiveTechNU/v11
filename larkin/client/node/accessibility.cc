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

#include <vector>
#include "client/node/accessibility.h"
#include "client/node/utils.h"
#include "core/accessibility/accessibility_tree.h"

using utils::window_to_object;
using a11y::AccessibilityWindow;
using a11y::AccessibilityTree;

namespace a11y {

void windows(napi_env env, napi_value exports) {
    napi_value accessibility_object;
    a_ok(napi_create_object(env, &accessibility_object));

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
        std::vector<AccessibilityWindow> windows = app_tree.get_windows();

        for (int i = 0; i < windows.size(); i++) {
            const AccessibilityWindow& window = windows[i];
            napi_value window_object;
            window_to_object(env, &window, &window_object);
            a_ok(napi_set_element(env, windows_array, i, window_object));
        }
        return windows_array;
    }, nullptr, &get_windows));

    a_ok(napi_set_named_property(env,
                                 accessibility_object,
                                 "getWindows",
                                 get_windows));
    a_ok(napi_set_named_property(env,
                                 exports,
                                 "accessibility",
                                 accessibility_object));
}

// Initialize all variables and functions
void init(napi_env env, napi_value exports, System* sys_ptr) {
    windows(env, exports);
}

};  // namespace environment
