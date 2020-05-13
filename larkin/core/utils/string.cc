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
