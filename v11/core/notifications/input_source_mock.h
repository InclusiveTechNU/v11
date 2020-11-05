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
#include <functional>
#include "core/notifications/input_source_base.h"
#include "core/notifications/input_source.h"
#include "core/notifications/notification.h"

namespace sys {
namespace tests {

const char kMockInputSourceName[] = "mock";

class MockInputSource : public InputSourceBase<NotificationType> {
 private:
    std::string name_ = std::string(kMockInputSourceName);

 public:
    MockInputSource() = default;
    void CallCallbackMethod(Notification<NotificationType>* notification);
    const std::string& GetInputSourceName() const;
};

}  // namespace tests
}  // namespace sys
