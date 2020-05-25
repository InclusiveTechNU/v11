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

#include "client/node/utils.h"

namespace utils {

char* string_from_value(napi_env env, napi_value value) {
    size_t value_len = -1;
    size_t value_len_read = -1;
    char* text_buffer = nullptr;
    napi_get_value_string_utf8(env, value, nullptr, 0, &value_len);

    if (value_len != -1) {
        text_buffer = new char[value_len+1];
        napi_status status;
        status = napi_get_value_string_utf8(env,
                                            value,
                                            text_buffer,
                                            value_len+1,
                                            &value_len_read);
        if (status != napi_ok) return nullptr;
        return text_buffer;
    }
    return nullptr;
}

};  // namespace utils