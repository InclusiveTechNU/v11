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
#include "larkin/environment/application/application_observer.h"

namespace app {

ApplicationObserver::ApplicationObserver(pid_t identifier) {
    /*_callback_handler = new std::function<void(NotificationType)>([](NotificationType type) {
        std::cout << "hey!\n";
    });*/
    _native_bridge = new ApplicationObserverBridge(identifier);
}

ApplicationObserver* ApplicationObserver::
                     create_observer(pid_t identifier) {
    return new ApplicationObserver(identifier);
}

/*void ApplicationObserver::add_observer_callback(NotificationType type,
                                                std::function<void()>* callback) {
    _callbacks.insert(std::pair<NotificationType,
                                std::function<void()>*>(type, callback));
}*/

ApplicationObserverBridge* ApplicationObserver::get_native_bridge() {
    return _native_bridge;
}

ApplicationObserver::~ApplicationObserver() {
    delete _native_bridge;
    //delete _callback_handler;
}

}  // namespace app
