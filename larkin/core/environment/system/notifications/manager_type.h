/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace sys {
namespace notifications {

// Notification managers can support a default
// system manager type or a custom type for group
// specific types of system notifications.
//    `system`: default system manager type
//    `custom`: a custom notification grouping
enum manager_type {
    system,
    custom
};

};  // namespace notifications
};  // namespace sys
