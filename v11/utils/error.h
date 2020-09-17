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


}  // namespace utils
