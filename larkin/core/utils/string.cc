/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <string.h>
#include "utils/string.h"

namespace utils {

char* string_copy(const char* text) {
    if (!text) {
        return nullptr;
    }

    int text_len = strlen(text);
    char* new_string = new char[text_len+1];

    for (int i = 0; text[i] != '\0'; i++) {
        new_string[i] = text[i];
    }

    new_string[text_len] = '\0';
    return new_string;
}

};  // namespace utils
