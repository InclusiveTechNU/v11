/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <stdexcept>
#include <string>

namespace utils {

enum error_code {
    ERROR_CODE_NONE,
    ERROR_FAILED_LINKING_MANAGER_BRIDGE,
    ERROR_NULL_OBSERVER
};

// Non-throwing error message data type
// containing a boolean that is true when
// a function completes.
struct error {
    bool completed;
    error_code message;
};


};  // namespace utils
