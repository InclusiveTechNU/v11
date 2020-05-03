/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <vector>
#include "environment/system/system_initializer.h"
#include "interaction/keyboard/keyboard_listener.h"

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

};  // namespace sys
