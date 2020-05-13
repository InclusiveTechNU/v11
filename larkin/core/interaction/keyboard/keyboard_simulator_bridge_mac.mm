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
#include <QuartzCore/QuartzCore.h>
#include "utils/definitions.h"
#include "interaction/keyboard/keyboard_simulator_bridge.h"
#include "interaction/keyboard/keycode_converter_mac.h"

namespace keyboard {

void KeyboardSimulatorBridge::hold_key(const keycode& key) {
    CGKeyCode converted_key = [KeycodeConverter keycodeAsNativeCode:key];
    CGEventRef* key_down_event = new_space(CGEventRef);
    *key_down_event = CGEventCreateKeyboardEvent(NULL,
                                                 converted_key,
                                                 true);
    CGEventPost(kCGHIDEventTap, *key_down_event);
    key_events[key] = (void*) key_down_event;
}

void KeyboardSimulatorBridge::release_key(const keycode& key) {
    CGKeyCode converted_key = [KeycodeConverter keycodeAsNativeCode:key];
    CGEventRef key_up_event = CGEventCreateKeyboardEvent(NULL,
                                                         converted_key,
                                                         false);
    CGEventPost(kCGHIDEventTap, key_up_event);

    CGEventRef* key_down_event = (CGEventRef*) key_events[key];
    CFRelease(*key_down_event);
    CFRelease(key_up_event);

    key_events.erase(key_events.find(key));
}

bool KeyboardSimulatorBridge::keycode_free(const keycode& key) {
    return key_events.find(key) == key_events.end();
}

};  // namespace keyboard
