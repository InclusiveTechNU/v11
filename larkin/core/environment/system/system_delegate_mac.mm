/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "environment/system/system_delegate_mac.h"
#include "environment/system/system_initializer.h"

@implementation SystemDelegate {
    // TODO(tommymchugh): Confirm this is not undefined behavior
    void* system_initializer;
    std::vector<std::function<void(void*)>*>* pending_actions;
}

- (void)attachInitializer:(void*)initializer {
    system_initializer = initializer;
}

- (void)attachPendingActions:(std::vector<std::function<void(void*)>*>*)actions {
    pending_actions = actions;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    sys::initializer sys_init = (sys::initializer) system_initializer;
    void* kb_listener = (*sys_init)();

    if (pending_actions) {
        for (std::function<void(void*)>* action : *pending_actions) {
            if (action) {
                (*action)(kb_listener);
            }
        }
    }
}

@end