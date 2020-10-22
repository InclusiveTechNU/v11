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
#include <functional>
#include "larkin/environment/system/platform/platform_info.h"
#include "larkin/environment/system/platform/platform.h"
#include "larkin/environment/system/notifications/notification_manager.h"
#include "larkin/environment/system/system_bridge.h"
#include "larkin/interaction/sound/sound_manager.h"
#include "larkin/interaction/keyboard/keyboard_listener.h"

using sys::NotificationManager;
using keyboard::KeyboardListener;
using sound::SoundManager;

namespace sys {

class System {
    SystemBridge* bridge = nullptr;
    Platform* platform_ = nullptr;

    NotificationManager* notification_center = nullptr;
    KeyboardListener* keyboard_listener = nullptr;
    SoundManager* _sound_manager = nullptr;

    std::vector<std::function<void(void*)>*>* pending_actions = nullptr;

 public:
    // Setups up system interaction and information interfaces
    System();
    const Platform* GetPlatform();
    NotificationManager* get_notification_center();
    SoundManager* get_sound_manager();
    KeyboardListener* get_keyboard_listener();

    // Forwards the event listener to the proper system event
    // service after all notification systems have been instantiated.
    // Uses template `L` for the action that the listener is looking for
    // and template `A` for the action to be performed once the event of
    // that action was identified.
    void add_event_listener(const keyboard::event::
                                  event_type& action,
                            const keyboard::callback& callback);
    void add_event_listener(const NotificationType& action,
                            NotificationCallback* callback);

    // Deallocates owned object
    ~System();
};

}  // namespace sys

