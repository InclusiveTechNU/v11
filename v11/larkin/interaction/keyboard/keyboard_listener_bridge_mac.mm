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
#include "larkin/interaction/keyboard/keycode_converter_mac.h"
#include "larkin/interaction/keyboard/keyboard_listener_bridge.h"
#include "larkin/interaction/keyboard/keyboard_event.h"

using utils::error;
using utils::error_code;
using keyboard::event::KeyboardEvent;

namespace keyboard {

error KeyboardListenerBridge::
register_global_observer(const global_observer* observer) {
    if (!observer) {
        return {true, error_code::ERROR_NULL_OBSERVER};
    }

    observer_ = observer;
    id key_event = [NSEvent addGlobalMonitorForEventsMatchingMask:NSEventMaskAny//NSEventMaskFlagsChanged
                           handler:^(NSEvent *event_native){
                        BOOL key_event_type = event_native.type == NSEventTypeKeyDown ||
                                              event_native.type == NSEventTypeKeyUp ||
                                              event_native.type == NSEventTypeFlagsChanged;
                        if (key_event_type) {
                            CGEventRef event_raw = [event_native CGEvent];
                            CGKeyCode event_code_raw = CGEventGetIntegerValueField(event_raw,
                                                                                   kCGKeyboardEventKeycode);
                            keycode event_code = [KeycodeConverter
                                                  nativeCodeAsKeycode:
                                                  event_code_raw];
                            event::event_type event_type = event::
                                                           event_type::KEY_DOWN;
                            if (event_native.type == NSEventTypeKeyUp) {
                                event_type = event::event_type::KEY_UP;
                            }
                            const keycode_index event_active = keycode_activated(event_code);
                            if (event_active.activated) {
                                activated_keycodes_.erase(event_active.index);
                            } else {
                                activated_keycodes_.push_back(event_code);
                            }
                            KeyboardEvent* event = new KeyboardEvent(event_type,
                                                                     event_code);
                            (*observer_)(event);
                        }
                   }];
    monitoring_event_ = (__bridge_retained monitor_event) key_event;
    registered_global_observer_ = true;
    return {false, error_code::ERROR_CODE_NONE};
}

const keycode_index KeyboardListenerBridge::keycode_activated(const keycode& code) {
    keycode_index index;
    index.index = activated_keycodes_.begin();
    for (int i = 0; i < activated_keycodes_.size(); i++) {
        const keycode& active_code = *index.index;
        if (active_code == code) {
            index.activated = true;
            return index;
        }
        index.index++;
    }
    return index;
}

KeyboardListenerBridge::~KeyboardListenerBridge() {
    [NSEvent removeMonitor: (__bridge_transfer id) monitoring_event_];
}

}  // namespace keyboard
