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
#include "accessibility/accessibility_window.h"

namespace a11y {
const char* AccessibilityWindow::get_title() const {
    AXUIElementRef app_ref = (AXUIElementRef) _native_element;
    CFTypeRef window_title_raw = nullptr;
    CFStringRef window_title_label = CFStringCreateWithCString(nullptr, "AXTitle", kCFStringEncodingUTF8);
    AXUIElementCopyAttributeValue(app_ref, window_title_label, &window_title_raw);
    assert(window_title_raw);

    NSString* window_title_str = (__bridge_transfer NSString*) window_title_raw;
    return [window_title_str UTF8String];
}
};  // namespace a11y
