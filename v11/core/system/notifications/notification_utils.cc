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

#include "core/system/notifications/notification_utils.h"
#include "core/system/notifications/notification_utils_bridge.h"

namespace sys {
namespace notifications {
namespace utils {

void* convert_notification_type_to_native(NotificationType type) {
    return __convert_notification_type_to_native(type);
}

};  // namespace utils
};  // namespace notifications
};  // namespace sys
