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
#include "larkin/environment/system/notifications/notification_utils_bridge.h"

namespace sys {
namespace utils {

void* __convert_notification_type_to_native(NotificationType type) {
    switch(type) {
        case NotificationType::kWindowDidMinimize:
            return (void*) kAXWindowMiniaturizedNotification;
        case NotificationType::kWindowDidDeminimize:
            return (void*) kAXWindowDeminiaturizedNotification;
        case NotificationType::kApplicationDidChangeMainWindow:
            return (void*) kAXMainWindowChangedNotification;
        case NotificationType::kApplicationDidChangeFocusedWindow:
            return (void*) kAXFocusedWindowChangedNotification;
        case NotificationType::kApplicationDidChangeFocusedUIElement:
            return (void*) kAXFocusedUIElementChangedNotification;
        case NotificationType::kApplicationDidCreateUIElement:
            return (void*) kAXCreatedNotification;
        case NotificationType::kApplicationDidCreateWindow:
            return (void*) kAXWindowCreatedNotification;
        case NotificationType::kApplicationDidRemoveElement:
            return (void*) kAXUIElementDestroyedNotification;
        case NotificationType::kWindowDidFinishMove:
            return (void*) kAXWindowMovedNotification;
        case NotificationType::kWindowDidFinishResize:
            return (void*) kAXWindowResizedNotification;
        case NotificationType::kUIElementDidResize:
            return (void*) kAXResizedNotification;
        case NotificationType::kUIElementDidMove:
            return (void*) kAXMovedNotification;
        case NotificationType::kUIElementDidChangeTitle:
            return (void*) kAXTitleChangedNotification;
        case NotificationType::kUIElementDidChangeValue:
            return (void*) kAXValueChangedNotification;
        case NotificationType::kUIElementDidRemove:
            return (void*) kAXUIElementDestroyedNotification;
        default:
            return nullptr;
    }
}

}  // namespace utils
}  // namespace sys