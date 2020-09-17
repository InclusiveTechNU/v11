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

#include <vector>
#include "larkin/environment/system/system_initializer.h"
#include "larkin/interaction/keyboard/keyboard_listener.h"

namespace sys {

typedef void* system_delegate;

class SystemBridge {
    initializer native_initializer = nullptr;
    system_delegate delegate = nullptr;
    keyboard::KeyboardListener* keyboard_listener = nullptr;
    std::vector<std::function<void(void*)>*>* pending_actions = nullptr;
 public:
    SystemBridge();
    keyboard::KeyboardListener* get_keyboard_listener();
    std::vector<std::function<void(void*)>*>* get_pending_actions();
    void remove_all_pending_actions();
    ~SystemBridge();
};

}  // namespace sys
