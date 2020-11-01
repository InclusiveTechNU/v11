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
#include "absl/container/btree_set.h"
#include "larkin/environment/system/system_base.h"
#include "larkin/environment/system/platform/platform.h"
#include "larkin/environment/system/notifications/notification_manager.h"
#include "larkin/environment/application/application.h"

using sys::NotificationManager;
using sys::Platform;
using app::Application;

namespace sys {

// Mac applications are directories that end with a `.app` extension.
// This constant allows for this extension to be appended to potential
// app name strings.
const char kApplicationFileExt[] = ".app";

// The mac filesystem uses a back slash character to distinguish seperations
// within the path of a file.
const char kNativeFileSeperator[] = "/";

class SystemMac : public SystemBase {
 private:
    static SystemMac* instance_;

    SystemMac();

    // Returns the native path of the application if it exists, or null if
    // the path could not be found. Assumes that name does not include
    // the native `.app` file extension.
    static std::string* GetApplicationPath(const std::string& name,
                                           const std::string& start_path);

    // Inherited From System Base Class
    void LoadRunningApplications();

 public:
    ~SystemMac();
    static SystemMac* GetInstance();

    // Inherited From System Base Class
    const void* GetRunningScreenReader() const;
    void StartApplicationNamed(const std::string& name) const;
    void StartApplicationAtPath(const std::string& path) const;
    void HideOtherApplications() const;
};

}  // namespace sys
