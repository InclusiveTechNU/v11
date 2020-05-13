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

#include "sys/types.h"

namespace app {

// Method types for identifying the information about
// a specific application. `bundle_id` is the specific
// string sequence corresponding to an app bundle
// such as: com.example.example. file_path is the
// application's location within the file system
enum app_id_type {
    bundle_id,
    file_path
};

enum visibility {
    hidden,
    visible
};

struct app_id {
    const char* id;
    app_id_type type;
};

// Specific static details about an application.
//    `local_name`: The localized name of the application.
//    `bundle_id`: The bundle identifier for the application.
struct app_info {
    const char* local_name;
    const char* bundle_id;
};

};  // namespace app
