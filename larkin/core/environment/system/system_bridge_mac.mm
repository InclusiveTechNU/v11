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

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <functional>
#include "utils/definitions.h"
#include "environment/system/system_bridge.h"
#include "environment/system/system_delegate_mac.h"

namespace sys {

SystemBridge::SystemBridge() {
    pending_actions = new std::vector<std::function<void(void*)>*>;
    native_initializer = new std::function<void*()>([&]() {
        keyboard_listener = new keyboard::KeyboardListener;
        return keyboard_listener;
    });

    // Initialize the listeners from the system delegate
    SystemDelegate* sys_delegate = [[SystemDelegate alloc] init];

    [sys_delegate attachInitializer: (void*) native_initializer];
    [sys_delegate attachPendingActions: pending_actions];
    NSApplication* application = [NSApplication sharedApplication];
    [application setDelegate:sys_delegate];

    // Transfer system delegate to larkin memory management
    delegate = (__bridge_retained system_delegate) sys_delegate;
}

keyboard::KeyboardListener* SystemBridge::get_keyboard_listener() {
    return keyboard_listener;
}

std::vector<std::function<void(void*)>*>* SystemBridge::get_pending_actions() {
    return pending_actions;
}

void SystemBridge::remove_all_pending_actions() {
    if (pending_actions) {
        for (std::function<void(void*)>* action : *pending_actions) {
            delete action;
        }
        delete pending_actions;
        pending_actions = nullptr;
    }
}

SystemBridge::~SystemBridge() {
    if (delegate) {
        __lk_unused__ (__bridge_transfer SystemDelegate*) delegate;
    }
    delete native_initializer;
    delete keyboard_listener;
    delete pending_actions;
}

};  // namespace sys
