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

#include <limits.h>
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "larkin/accessibility/accessibility_tree.h"
#include "larkin/accessibility/accessibility_element.h"
#include "larkin/environment/system/notifications/notification.h"

using sys::NotificationType;

namespace a11y {

std::vector<AccessibilityWindow*> AccessibilityTree::get_windows() {
    std::vector<AccessibilityWindow*> windows;
    AXUIElementRef app_ref = AXUIElementCreateApplication(_app->get_process_id());
    CFArrayRef window_array_raw = nullptr;
    CFStringRef window_label = CFStringCreateWithCString(nullptr, "AXWindows", kCFStringEncodingUTF8);
    AXUIElementCopyAttributeValues(app_ref, window_label, 0, INT_MAX, &window_array_raw);
    if (!window_array_raw) {
        return windows;
    }

    NSArray* window_array = (__bridge NSArray*) window_array_raw;
    (__bridge_transfer NSString*) window_label;
    for (int i = 0; i < [window_array count]; i++) {
        const void* window_ptr = (__bridge void*) window_array[i];
        windows.push_back(new AccessibilityWindow(_app, window_ptr));
    }
    return windows;
}

}  // namespace a11y
