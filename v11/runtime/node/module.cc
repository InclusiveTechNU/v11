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

#include <node/node_api.h>
#include <uv.h>
#include <sys/event.h>
#include <functional>
#include <thread>
#include <future>
#include <iostream>
#include <chrono>
#include "get_uv_event_loop/include/get-uv-event-loop-napi.h"
#include "runtime/node/interaction.h"
#include "runtime/node/accessibility.h"
#include "runtime/node/utils.h"
#include "runtime/node/environment.h"
#include "core/environment/system/system.h"
#include "core/environment/system/system_instance.h"
#include "utils/run_main.h"

using utils::run_non_block_loop;
using sys::System;
using utils::pause_main_loop;
using utils::create_main_app;

namespace core {

napi_value create_set_immediate_func(napi_env env);

void check_for_node_event(int backend_fd) {
    while (true) {
        struct kevent events;
        while (kevent(backend_fd, nullptr, 0, &events, 1, nullptr) <= 0) {}
        pause_main_loop();
    }
}

napi_value process_event_loop(napi_env env, napi_callback_info info) {
    napi_value global, process, next_tick;
    a_ok(napi_get_global(env, &global));
    a_ok(napi_get_named_property(env, global, "process", &process));
    a_ok(napi_get_named_property(env, process, "nextTick", &next_tick));

    // Identify the timeout period of the event loop
    uv_loop_t* node_loop = get_uv_event_loop(env);
    run_non_block_loop(node_loop);

    napi_value callback_func = create_set_immediate_func(env);
    a_ok(napi_call_function(env, process, next_tick, 1, &callback_func, nullptr));
    return nullptr;
}

napi_value set_immediate_func(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value global, set_immediate, proc_loop;
    a_ok(napi_get_global(env, &global));
    a_ok(napi_get_named_property(env, global, "setImmediate", &set_immediate));
    a_ok(napi_create_function(env, nullptr, 0, process_event_loop, nullptr, &proc_loop));
    napi_value* argv = &proc_loop;
    a_ok(napi_call_function(env, global, set_immediate, argc, argv, nullptr));
    return nullptr;
}

napi_value create_set_immediate_func(napi_env env) {
    napi_value set_immediate;
    a_ok(napi_create_function(env, nullptr, 0, set_immediate_func, nullptr, &set_immediate));
    return set_immediate;
}

void setup_event_loop(napi_env env, napi_value exports) {
    create_main_app();
    // Check for new events
    uv_loop_t* node_loop = get_uv_event_loop(env);
    int backend_fd = uv_backend_fd(node_loop);
    std::thread node_events = std::thread(check_for_node_event, backend_fd);
    node_events.detach();

    // Setup non-blocking recursive process.nextTick
    napi_value global;
    napi_value event_loop_func = create_set_immediate_func(env);
    a_ok(napi_get_global(env, &global));
    a_ok(napi_call_function(env, global, event_loop_func, 0, nullptr, nullptr));
}

napi_value init(napi_env env, napi_value exports) {
    // Add sub platform APIs
    interaction::init(env, exports);
    environment::init(env, exports);
    a11y::init(env, exports);

    setup_event_loop(env, exports);
    return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace core
