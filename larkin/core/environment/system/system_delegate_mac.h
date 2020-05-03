/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>
#include <AVFoundation/AVFoundation.h>
#include <functional>
#include <vector>

@interface SystemDelegate : NSObject <NSApplicationDelegate>

- (void)attachInitializer:(void*)initializer;
- (void)attachPendingActions:(std::vector<std::function<void(void*)>*>*)actions;
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;
@end
