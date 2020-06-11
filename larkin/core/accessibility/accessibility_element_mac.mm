
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
#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "accessibility/accessibility_element.h"

namespace a11y {

std::vector<AccessibilityElement*> AccessibilityElement::get_children() const {
    std::vector<AccessibilityElement*> children;
    AXUIElementRef app_ref = (AXUIElementRef) _native_element;

    CFArrayRef children_array_raw = nullptr;
    CFStringRef children_label = CFStringCreateWithCString(nullptr, "AXChildren", kCFStringEncodingUTF8);
    AXUIElementCopyAttributeValues(app_ref, children_label, 0, INT_MAX, &children_array_raw);
    if (!children_array_raw) {
        return children;
    }

    NSArray* children_array = (__bridge_transfer NSArray*) children_array_raw;
    (__bridge_transfer NSString*) children_label;
    for (int i = 0; i < [children_array count]; i++) {
        AXUIElementRef child = (AXUIElementRef) children_array[i];
        children.push_back(new AccessibilityElement(ElementType::UNKNOWN, (void*) child));
    }
    return children;
}

const char* AccessibilityElement::get_value(const char* name) const {
    AXUIElementRef app_ref = (AXUIElementRef) _native_element;
    /*CFArrayRef children_array_raw = nullptr;
    AXUIElementCopyAttributeNames(app_ref, &children_array_raw);
    NSLog(@"%@", children_array_raw);*/

    CFTypeRef value_raw = nullptr;
    CFStringRef value_label = CFStringCreateWithCString(nullptr, name, kCFStringEncodingUTF8);
    AXUIElementCopyAttributeValue(app_ref, value_label, &value_raw);
    if (!value_raw) {
        return nullptr;
    }

    if (CFGetTypeID(value_raw) == CFStringGetTypeID()) {
        NSString* value = (__bridge_transfer NSString*) value_raw;
        return [value UTF8String];
    } else if (CFGetTypeID(value_raw) == CFNumberGetTypeID()) {
        NSNumber* value = (__bridge_transfer NSNumber*) value_raw;
        return [[value stringValue] UTF8String];
    }
    return nullptr;
}

void AccessibilityElement::set_value(const char* value) {
    AXUIElementRef app_ref = (AXUIElementRef) _native_element;
    CFStringRef value_label = CFStringCreateWithCString(nullptr, "AXValue", kCFStringEncodingUTF8);
    CFStringRef value_entry = CFStringCreateWithCString(nullptr, value, kCFStringEncodingUTF8);
    AXUIElementSetAttributeValue(app_ref, value_label, value_entry);
}

std::vector<std::string> AccessibilityElement::get_actions() const {
    std::vector<std::string> actions;
    AXUIElementRef app_ref = (AXUIElementRef) _native_element;

    CFArrayRef action_array_raw = nullptr;
    AXUIElementCopyActionNames(app_ref, &action_array_raw);
    if (!action_array_raw) {
        return actions;
    }

    NSArray* action_array = (__bridge_transfer NSArray*) action_array_raw;
    for (int i = 0; i < [action_array count]; i++) {
        NSString* action_name = (NSString*) action_array[i];
        actions.push_back(std::string([action_name UTF8String]));
    }
    return actions;
}

void AccessibilityElement::perform_action(const char* name) {
    AXUIElementRef app_ref = (AXUIElementRef) _native_element;
    CFStringRef action_name = CFStringCreateWithCString(nullptr, name, kCFStringEncodingUTF8);
    AXUIElementPerformAction(app_ref, action_name);
}

};  // namespace a11y
