/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
