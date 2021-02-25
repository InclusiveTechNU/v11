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

#include "core/accessibility/accessibility_element.h"

namespace a11y {

AccessibilityElement::AccessibilityElement(Application* app,
                                           ElementType type,
                                           const void* native_element) :
                                           _app(app),
                                           _type(type),
                                           _native_element(native_element) {}

const char* AccessibilityElement::get_type() const {
    return get_value("AXRole");
}

const char* AccessibilityElement::get_label() const {
    return get_value("AXDescription");
}

const char* AccessibilityElement::get_title() const {
    return get_value("AXTitle");
}
const char* AccessibilityElement::get_value() const {
    return get_value("AXValue");
}

const char* AccessibilityElement::get_description() const {
    return get_value("AXRoleDescription");
}

const char* AccessibilityElement::get_help_text() const {
    return get_value("AXHelp");
}

const void* AccessibilityElement::get_native_element() const {
    return _native_element;
}

}  // namespace a11y
