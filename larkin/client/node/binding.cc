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

#include <functional>
#include <node_api.h>
#include "client/node/interaction.h"
#include "client/node/environment.h"
#include "core/utils/run_main.h"

using utils::run_main_loop;

namespace larkin {

napi_value init(napi_env env, napi_value exports) {
    // Add sub platform APIs
    interaction::init(env, exports);
    environment::init(env, exports);

    napi_status status;
    // * utils.run() -> void
    // Implement runner method to run a non-blocking loop to
    // listen for shortcuts and keyboard handlers
    napi_value utils;
    status = napi_create_object(env, &utils);
    if (status != napi_ok) {
        napi_throw_error(env, nullptr, "Failed to init utils object");
    }

    napi_value run_func;
    status = napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        run_main_loop();
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

    return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace larkin
