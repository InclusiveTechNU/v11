/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace utils {

// Creates a copy of a string and transfers
// the string ownership to the caller
char* string_copy(const char* text);

};  // namespace utils
