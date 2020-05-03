/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <vector>
#include <functional>
#include "environment/system/platform/platform_info.h"
#include "environment/system/platform/platform.h"
#include "environment/system/notifications/notification_manager.h"
#include "environment/system/system_bridge.h"
#include "interaction/keyboard/keyboard_listener.h"

using sys::platform::platform_info;
using sys::notifications::NotificationManager;
using keyboard::KeyboardListener;

namespace sys {

class System {
    SystemBridge* bridge = nullptr;
    const platform_info platform;
    NotificationManager* notification_center = nullptr;
    KeyboardListener* keyboard_listener = nullptr;
    std::vector<std::function<void(void*)>*>* pending_actions = nullptr;

 public:
    // Setups up system interaction and information interfaces
    System();

    // Forwards the event listener to the proper system event
    // service after all notification systems have been instantiated.
    // Uses template `L` for the action that the listener is looking for
    // and template `A` for the action to be performed once the event of
    // that action was identified.
    void add_event_listener(const keyboard::event::
                                  event_type& action,
                            const keyboard::callback& callback);
    void add_event_listener(const notifications::notification_type& action,
                            const notifications::callback& callback);

    // Deallocates owned object
    ~System();
};

};  // namespace sys

