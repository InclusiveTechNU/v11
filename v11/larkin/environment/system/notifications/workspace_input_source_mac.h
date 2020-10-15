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
#include "larkin/environment/system/notifications/input_source_base.h"

namespace sys {

const char kWorkspaceInputSourceMacName[] = "workspace_mac";

class WorkspaceInputSourceMac : public InputSourceBase {
 private:
    const std::string name_ = std::string(kWorkspaceInputSourceMacName);
    void* notification_center_ = nullptr;

    void RegisterNotificationObserver();

 public:
    WorkspaceInputSourceMac();
    ~WorkspaceInputSourceMac();
    const std::string& GetInputSourceName() const;
};

}  // namespace sys
