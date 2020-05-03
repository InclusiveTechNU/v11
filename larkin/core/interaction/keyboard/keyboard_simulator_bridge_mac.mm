/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
