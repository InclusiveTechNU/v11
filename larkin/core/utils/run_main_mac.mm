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
#include <QuartzCore/QuartzCore.h>
#include "utils/run_main.h"

namespace utils {

void call_from_main(const std::function<void()>& func) {
    dispatch_async(dispatch_get_main_queue(), ^{
        func();
    });
}

void create_main_app() {
    [NSApplication sharedApplication];
}

void send_event() {
    NSApplication* app = [NSApplication sharedApplication];
    NSEvent* event = [app nextEventMatchingMask:NSAnyEventMask
                          untilDate:[NSDate distantPast]
                          inMode:NSEventTrackingRunLoopMode
                          dequeue:YES];
    [app sendEvent:event];
}

void run_main_loop() {
    NSApplication* app = [NSApplication sharedApplication];
    while (true) {
        NSEvent* event = [app nextEventMatchingMask:NSAnyEventMask
                              untilDate:[NSDate distantFuture]
                              inMode:NSDefaultRunLoopMode
                              dequeue:YES];
        [app sendEvent:event];
    }
}

void pause_main_loop() {
    if ([NSApplication sharedApplication].running) {
        [[NSApplication sharedApplication] stop: nil];
    }
}

};  // namespace utils
