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
#include <vector>

namespace a11y {

enum ElementType {
    WINDOW,
    UNKNOWN
};

class AccessibilityElement {
 protected:
    ElementType _type;
    const void* _native_element;
    const char* get_value(const char* name) const;
 public:
    explicit AccessibilityElement(ElementType type,
                                  const void* native_element);
    std::vector<AccessibilityElement*> get_children() const;
    std::vector<std::string> get_actions() const;
    void perform_action(const char* name);
    void set_value(const char* value);
    const char* get_type() const;
    const char* get_label() const;
    const char* get_title() const;
    const char* get_value() const;
    const char* get_description() const;
};

};  // namespace a11y
