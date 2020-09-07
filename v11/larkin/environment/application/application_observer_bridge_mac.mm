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

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <functional>
#include "larkin/environment/application/application_observer_bridge.h"

namespace app {

void native_observer_callback(AXObserverRef observer,
              AXUIElementRef element,
              CFStringRef notificationName,
              void *refCon) { 
    std::function<void()>* callback = (std::function<void()>*) refCon;
    (*callback)();
} 

ApplicationObserverBridge::ApplicationObserverBridge(pid_t identifier) {
    // Create the native AXObserverRef
    AXObserverCallback observer_callback = native_observer_callback;
    AXObserverRef observer_ref = nullptr;
    AXError create_err = AXObserverCreate(identifier,
                                          observer_callback,
                                          &observer_ref);
    if (create_err != kAXErrorSuccess && !observer_ref) {
        // TODO(tommymchugh): Handle this error
        NSLog(@"Welcome to error town");
    }
    // Convert the reference into a native object pointer for bridging
    _native_object = (void*) observer_ref;
    CFRunLoopAddSource([[NSRunLoop currentRunLoop] getCFRunLoop],
        AXObserverGetRunLoopSource(observer_ref),
        kCFRunLoopDefaultMode);
}

void* ApplicationObserverBridge::get_native_observer() {
    return _native_object;
}

};  // namespace app
