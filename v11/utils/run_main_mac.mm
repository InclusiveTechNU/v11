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

void send_event(int time) {
    NSDate* date = [NSDate dateWithTimeIntervalSinceNow:time];
    NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                        untilDate:date
                                           inMode:NSDefaultRunLoopMode
                                          dequeue:YES];
    if (event) {
        [NSApp sendEvent:event];
    }
}

void run_main_loop() {
    NSApplication* app = [NSApplication sharedApplication];
    while (true) {
        NSEvent* event = [app nextEventMatchingMask:NSEventMaskAny
                              untilDate:[NSDate distantFuture]
                              inMode:NSDefaultRunLoopMode
                              dequeue:YES];
        [app sendEvent:event];
    }
}

void pause_main_loop() {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                        location:NSMakePoint(0, 0)
                                   modifierFlags:0
                                       timestamp:0
                                    windowNumber:0
                                         context:nil
                                         subtype:0
                                           data1:0
                                           data2:0];
        [NSApp postEvent:event atStart:YES];
    });
}

}  // namespace utils
