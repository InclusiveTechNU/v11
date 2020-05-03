/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <QuartzCore/QuartzCore.h>
#include "utils/run_main.h"

namespace utils {

void run_main_loop() {
    [NSApp run];
}

};  // namespace utils
