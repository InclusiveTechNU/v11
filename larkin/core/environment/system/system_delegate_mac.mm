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