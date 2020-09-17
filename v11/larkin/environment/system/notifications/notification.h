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

#include <string>
#include "absl/container/flat_hash_map.h"

namespace sys {
namespace notifications {

// Platform indepdent notification identifier names
enum notification_type {
    kUnknown,

    // Hardware Notifications    
    kDeviceDidMount,
    kDeviceDidUnmount,

    // System Notifications
    kSystemDidWake,
    kSystemDidSleep,
    kSystemWillPowerOff,

    // Accessibility Notifications
    kAccessibilityDidChange,

    // Application Lifecycle Notifications
    kApplicationDidLaunch,
    kApplicationDidTerminate,
    kApplicationDidHide,
    kApplicationDidUnhide,
    kApplicationDidChangeMainWindow,
    kApplicationDidChangeFocusedWindow,
    kApplicationDidChangeFocusedUIElement,
    kApplicationDidCreateUIElement,
    kApplicationDidCreateWindow,
    kApplicationDidRemoveElement,

    // Window Element Notifications
    kWindowDidFinishMove,
    kWindowDidFinishResize,
    kWindowDidMinimize,
    kWindowDidDeminimize,

    // Application UI Element Notifications
    kUIElementDidResize,
    kUIElementDidMove,
    kUIElementDidChangeTitle,
    kUIElementDidChangeValue,
    kUIElementDidRemove
};

// A platform indepdent structure containining the
// details of the observed notification.
class Notification {
 public:
    virtual ~Notification();

    // Returns the specific type of action identifier that the notification
    // is linked to.
    virtual notification_type GetType() = 0;
};

}  // namespace notifications
}  // namespace sys
