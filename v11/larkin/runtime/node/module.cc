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
#include <functional>
#include <node/uv.h>
#include <node/node_api.h>
#include "get_uv_event_loop/include/get-uv-event-loop-napi.h"
#include "larkin/runtime/node/interaction.h"
#include "larkin/runtime/node/accessibility.h"
#include "larkin/runtime/node/utils.h"
#include "larkin/runtime/node/environment.h"
#include "larkin/environment/system/system.h"

using utils::run_non_block_loop;
using sys::System;

namespace larkin {

void setup_event_loop(napi_env env, napi_value exports) {
    napi_status status;
    napi_value utils;
    status = napi_create_object(env, &utils);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to init utils object");
    }

    napi_value run_func;
    status = napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        uv_loop_t* node_loop = get_uv_event_loop(env);
        run_non_block_loop(node_loop);
        return nullptr;
    }, nullptr, &run_func);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to init utils/run function");
    }

    status = napi_set_named_property(env, utils, "run", run_func);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to set utils/run function");
    }
    status = napi_set_named_property(env, exports, "utils", utils);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to set utils object");
    }
}

napi_value init(napi_env env, napi_value exports) {
    System* main_sys = new System();

    // Add sub platform APIs
    interaction::init(env, exports, main_sys);
    environment::init(env, exports, main_sys);
    a11y::init(env, exports, main_sys);

    setup_event_loop(env, exports);
    return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace larkin
