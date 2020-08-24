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

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "environment/system/notifications/notification_utils_bridge.h"

namespace sys {
namespace notifications {
namespace utils {

void* __convert_notification_type_to_native(notification_type type) {
    switch(type) {
        case notification_type::WINDOW_ELEMENT_DID_MINIMIZE:
            return (void*) kAXWindowMiniaturizedNotification;
        case notification_type::WINDOW_ELEMENT_DID_DEMINIMIZE:
            return (void*) kAXWindowDeminiaturizedNotification;
        case notification_type::APPLICATION_DID_CHANGE_MAIN_WINDOW:
            return (void*) kAXMainWindowChangedNotification;
        case notification_type::APPLICATION_DID_CHANGE_FOCUSED_WINDOW:
            return (void*) kAXFocusedWindowChangedNotification;
        case notification_type::APPLICATION_DID_CHANGE_FOCUSED_UI_ELEMENT:
            return (void*) kAXFocusedUIElementChangedNotification;
        case notification_type::APPLICATION_DID_CREATE_UI_ELEMENT:
            return (void*) kAXCreatedNotification;
        case notification_type::APPLICATION_DID_CREATE_WINDOW:
            return (void*) kAXWindowCreatedNotification;
        case notification_type::APPLICATION_DID_REMOVE_ELEMENT:
            return (void*) kAXUIElementDestroyedNotification;
        case notification_type::WINDOW_ELEMENT_DID_FINISH_MOVE:
            return (void*) kAXWindowMovedNotification;
        case notification_type::WINDOW_ELEMENT_DID_FINISH_RESIZE:
            return (void*) kAXWindowResizedNotification;
        case notification_type::UI_ELEMENT_DID_RESIZE:
            return (void*) kAXResizedNotification;
        case notification_type::UI_ELEMENT_DID_MOVE:
            return (void*) kAXMovedNotification;
        case notification_type::UI_ELEMENT_DID_CHANGE_TITLE:
            return (void*) kAXTitleChangedNotification;
        case notification_type::UI_ELEMENT_DID_CHANGE_VALUE:
            return (void*) kAXValueChangedNotification;
        case notification_type::UI_ELEMENT_REMOVED:
            return (void*) kAXUIElementDestroyedNotification;
        default:
            return nullptr;
    }
}

};  // namespace utils
};  // namespace notifications
};  // namespace sys