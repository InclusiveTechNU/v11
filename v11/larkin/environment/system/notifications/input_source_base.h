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
#include "larkin/environment/system/notifications/input_source.h"
#include "larkin/environment/system/notifications/notification.h"

namespace sys {

// Default name for all InputSources that are derived from the
// InputSourceBase base class implementation.
const char kBaseInputSourceName[] = "base";

// Implementation of InputSource that can be used by other
// platforms to build OS-specific input sources.
template <typename Type>
class InputSourceBase : public InputSource<Type> {
 private:
     // The name of the type of notifications that are coming into the
    // input source.
    const std::string name_ = std::string(kBaseInputSourceName);

 protected:
    // The standard settings that control the management of
    // incoming notifications.
    InputSourceSettings settings_;

    // A vector of notifications owned by the InputSource until they are
    // cleared by the classe's memory mangement.
    std::vector<Notification<Type>*> memory_;

    // A callback function that is used to
    InputSourceCallback<Type>* callback_ = nullptr;

    // From InputSource parent class
    void StoreNotification(Notification<Type>* notification);

 public:
    virtual ~InputSourceBase();

    // From InputSource parent class
    void SetCallback(InputSourceCallback<Type>* callback);
    const InputSourceCallback<Type>* GetCallback() const;
    const InputSourceSettings& GetSettings() const;
    bool IsEnabled() const;
    virtual void SetEnabled(bool enabled);
    void SetStoringMemory(bool storing);
    bool IsStoringMemory() const;
    void ClearMemory();
    const std::vector<Notification<Type>*>* GetMemory() const;
    virtual const std::string& GetInputSourceName() const;
};

}  // namespace sys

#include "larkin/environment/system/notifications/input_source_base_inl.h"
