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

#include <sys/types.h>
#include <map>
#include <functional>
#include "larkin/environment/application/application_observer_bridge.h"
#include "larkin/environment/system/notifications/notification.h"

using sys::notifications::notification_type;

namespace app {

class ApplicationObserver {
 private:
    std::function<void(notification_type)>* _callback_handler = nullptr;
    std::map<notification_type, std::function<void()>*> _callbacks;
    ApplicationObserverBridge* _native_bridge = nullptr;
    explicit ApplicationObserver(pid_t identifier);

 public:
    // Creates an application observer for the given application
    // and passes the ownership of the observer to the
    // caller, i.e. the given application.
    static ApplicationObserver* create_observer(pid_t identifier);
    void add_observer_callback(notification_type type,
                               std::function<void()>* callback);
    ~ApplicationObserver();
    ApplicationObserverBridge* get_native_bridge();
};

};  // namespace app
