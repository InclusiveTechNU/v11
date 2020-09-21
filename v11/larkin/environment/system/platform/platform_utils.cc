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

#include <sstream>
#include "larkin/environment/system/platform/platform_utils.h"

namespace sys {

Version PlatformUtils::StringToVersion(const std::string& str) {
    Version conv_version = {0, 0, 0};
    uint16_t* focused_num = &(conv_version.major_version);
    std::size_t start = 0;
    for (std::size_t i = 0; i <= str.size(); i++) {\
        if (str[i] == '.' || i == str.size()) {
            std::stringstream num_stream;
            num_stream << str.substr(start, i-start);
            num_stream >> *focused_num;
            start = i+1;
            if (focused_num == &(conv_version.major_version)) {
                focused_num = &(conv_version.minor_version);
            } else if (focused_num == &(conv_version.minor_version)) {
                focused_num = &(conv_version.patch_version);
            } else {
                break;
            }
        }
    }
    return conv_version;
}

}  // namespace sys
