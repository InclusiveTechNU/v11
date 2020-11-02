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

#include <Carbon/Carbon.h>
#include "core/devices/keyboard/keycode_converter_mac.h"

using keyboard::keycode;
using keyboard::keycode_to_uint;
using keyboard::uint_to_keycode;

@implementation KeycodeConverter

+(NSDictionary<NSNumber*, NSNumber*>*) fetchConversionMap {
    return @{
        @(keycode_to_uint(keyboard::NUM_0_KEY)) : @(kVK_ANSI_0),
        @(keycode_to_uint(keyboard::NUM_1_KEY)) : @(kVK_ANSI_1),
        @(keycode_to_uint(keyboard::NUM_2_KEY)) : @(kVK_ANSI_2),
        @(keycode_to_uint(keyboard::NUM_3_KEY)) : @(kVK_ANSI_3),
        @(keycode_to_uint(keyboard::NUM_4_KEY)) : @(kVK_ANSI_4),
        @(keycode_to_uint(keyboard::NUM_5_KEY)) : @(kVK_ANSI_5),
        @(keycode_to_uint(keyboard::NUM_6_KEY)) : @(kVK_ANSI_6),
        @(keycode_to_uint(keyboard::NUM_7_KEY)) : @(kVK_ANSI_7),
        @(keycode_to_uint(keyboard::NUM_8_KEY)) : @(kVK_ANSI_8),
        @(keycode_to_uint(keyboard::NUM_9_KEY)) : @(kVK_ANSI_9),

        @(keycode_to_uint(keyboard::A_KEY)) : @(kVK_ANSI_A),
        @(keycode_to_uint(keyboard::S_KEY)) : @(kVK_ANSI_S),
        @(keycode_to_uint(keyboard::D_KEY)) : @(kVK_ANSI_D),
        @(keycode_to_uint(keyboard::F_KEY)) : @(kVK_ANSI_F),
        @(keycode_to_uint(keyboard::H_KEY)) : @(kVK_ANSI_H),
        @(keycode_to_uint(keyboard::G_KEY)) : @(kVK_ANSI_G),
        @(keycode_to_uint(keyboard::Z_KEY)) : @(kVK_ANSI_Z),
        @(keycode_to_uint(keyboard::X_KEY)) : @(kVK_ANSI_X),
        @(keycode_to_uint(keyboard::C_KEY)) : @(kVK_ANSI_C),
        @(keycode_to_uint(keyboard::V_KEY)) : @(kVK_ANSI_V),
        @(keycode_to_uint(keyboard::B_KEY)) : @(kVK_ANSI_B),
        @(keycode_to_uint(keyboard::Q_KEY)) : @(kVK_ANSI_Q),
        @(keycode_to_uint(keyboard::W_KEY)) : @(kVK_ANSI_W),
        @(keycode_to_uint(keyboard::E_KEY)) : @(kVK_ANSI_E),
        @(keycode_to_uint(keyboard::R_KEY)) : @(kVK_ANSI_R),
        @(keycode_to_uint(keyboard::Y_KEY)) : @(kVK_ANSI_Y),
        @(keycode_to_uint(keyboard::T_KEY)) : @(kVK_ANSI_T),
        @(keycode_to_uint(keyboard::O_KEY)) : @(kVK_ANSI_O),
        @(keycode_to_uint(keyboard::U_KEY)) : @(kVK_ANSI_U),
        @(keycode_to_uint(keyboard::I_KEY)) : @(kVK_ANSI_I),
        @(keycode_to_uint(keyboard::P_KEY)) : @(kVK_ANSI_P),
        @(keycode_to_uint(keyboard::L_KEY)) : @(kVK_ANSI_L),
        @(keycode_to_uint(keyboard::J_KEY)) : @(kVK_ANSI_J),
        @(keycode_to_uint(keyboard::K_KEY)) : @(kVK_ANSI_K),
        @(keycode_to_uint(keyboard::M_KEY)) : @(kVK_ANSI_M),
        @(keycode_to_uint(keyboard::N_KEY)) : @(kVK_ANSI_N),

        @(keycode_to_uint(keyboard::MINUS_KEY)) : @(kVK_ANSI_Minus),
        @(keycode_to_uint(keyboard::EQUAL_KEY)) : @(kVK_ANSI_Equal),

        @(keycode_to_uint(keyboard::RIGHT_BRACKET_KEY)) : @(kVK_ANSI_RightBracket),
        @(keycode_to_uint(keyboard::LEFT_BRACKET_KEY)) : @(kVK_ANSI_LeftBracket),

        @(keycode_to_uint(keyboard::QUOTE_KEY)) : @(kVK_ANSI_Quote),
        @(keycode_to_uint(keyboard::SEMICOLON_KEY)) : @(kVK_ANSI_Semicolon),
        @(keycode_to_uint(keyboard::BACKSLASH_KEY)) : @(kVK_ANSI_Backslash),
        @(keycode_to_uint(keyboard::COMMA_KEY)) : @(kVK_ANSI_Comma),
        @(keycode_to_uint(keyboard::PERIOD_KEY)) : @(kVK_ANSI_Period),
        @(keycode_to_uint(keyboard::SLASH_KEY)) : @(kVK_ANSI_Slash),
        @(keycode_to_uint(keyboard::GRAVE_KEY)) : @(kVK_ANSI_Grave),

        @(keycode_to_uint(keyboard::RETURN_KEY)) : @(kVK_Return),
        @(keycode_to_uint(keyboard::TAB_KEY)) : @(kVK_Tab),

        @(keycode_to_uint(keyboard::SPACE_KEY)) : @(kVK_Space),
        @(keycode_to_uint(keyboard::DELETE_KEY)) : @(kVK_Delete),
        @(keycode_to_uint(keyboard::FORWARD_DELETE_KEY)) : @(kVK_ForwardDelete),

        @(keycode_to_uint(keyboard::ESCAPE_KEY)) : @(kVK_Escape),
        @(keycode_to_uint(keyboard::COMMAND_KEY)) : @(kVK_Command),
        @(keycode_to_uint(keyboard::SHIFT_LEFT_KEY)) : @(kVK_Shift),
        @(keycode_to_uint(keyboard::CAPSLOCK_KEY)) : @(kVK_CapsLock),
        @(keycode_to_uint(keyboard::OPTION_LEFT_KEY)) : @(kVK_Option),
        @(keycode_to_uint(keyboard::CONTROL_LEFT_KEY)) : @(kVK_Control),
        @(keycode_to_uint(keyboard::SHIFT_RIGHT_KEY)) : @(kVK_RightShift),
        @(keycode_to_uint(keyboard::OPTION_RIGHT_KEY)) : @(kVK_RightOption),
        @(keycode_to_uint(keyboard::CONTROL_RIGHT_KEY)) : @(kVK_RightControl),
        @(keycode_to_uint(keyboard::END_KEY)) : @(kVK_End),

        @(keycode_to_uint(keyboard::VOLUME_UP_KEY)) : @(kVK_VolumeUp),
        @(keycode_to_uint(keyboard::VOLUME_DOWN_KEY)) : @(kVK_VolumeDown),
        @(keycode_to_uint(keyboard::VOLUME_MUTE_KEY)) : @(kVK_Mute),

        @(keycode_to_uint(keyboard::HELP_KEY)) : @(kVK_Help),
        @(keycode_to_uint(keyboard::HOME_KEY)) : @(kVK_Home),

        @(keycode_to_uint(keyboard::PAGE_UP_KEY)) : @(kVK_PageUp),
        @(keycode_to_uint(keyboard::PAGE_DOWN_KEY)) : @(kVK_PageDown),

        @(keycode_to_uint(keyboard::LEFT_ARROW_KEY)) : @(kVK_LeftArrow),
        @(keycode_to_uint(keyboard::RIGHT_ARROW_KEY)) : @(kVK_RightArrow),
        @(keycode_to_uint(keyboard::DOWN_ARROW_KEY)) : @(kVK_DownArrow),
        @(keycode_to_uint(keyboard::UP_ARROW_KEY)) : @(kVK_UpArrow),

        @(keycode_to_uint(keyboard::KEYPAD_NUM_0_KEY)) : @(kVK_ANSI_Keypad0),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_1_KEY)) : @(kVK_ANSI_Keypad1),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_2_KEY)) : @(kVK_ANSI_Keypad2),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_3_KEY)) : @(kVK_ANSI_Keypad3),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_4_KEY)) : @(kVK_ANSI_Keypad4),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_5_KEY)) : @(kVK_ANSI_Keypad5),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_6_KEY)) : @(kVK_ANSI_Keypad6),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_7_KEY)) : @(kVK_ANSI_Keypad7),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_8_KEY)) : @(kVK_ANSI_Keypad8),
        @(keycode_to_uint(keyboard::KEYPAD_NUM_9_KEY)) : @(kVK_ANSI_Keypad9),
        @(keycode_to_uint(keyboard::KEYPAD_DECIMAL_KEY)) : @(kVK_ANSI_KeypadDecimal),
        @(keycode_to_uint(keyboard::KEYPAD_MULTIPLY_KEY)) : @(kVK_ANSI_KeypadMultiply),
        @(keycode_to_uint(keyboard::KEYPAD_PLUS_KEY)) : @(kVK_ANSI_KeypadPlus),
        @(keycode_to_uint(keyboard::KEYPAD_CLEAR_KEY)) : @(kVK_ANSI_KeypadClear),
        @(keycode_to_uint(keyboard::KEYPAD_DIVIDE_KEY)) : @(kVK_ANSI_KeypadDivide),
        @(keycode_to_uint(keyboard::KEYPAD_ENTER_KEY)) : @(kVK_ANSI_KeypadEnter),
        @(keycode_to_uint(keyboard::KEYPAD_MINUS_KEY)) : @(kVK_ANSI_KeypadMinus),
        @(keycode_to_uint(keyboard::KEYPAD_EQUALS_KEY)) : @(kVK_ANSI_KeypadEquals),

        @(keycode_to_uint(keyboard::FUNCTION_KEY)) : @(kVK_Function),
        @(keycode_to_uint(keyboard::F1_KEY)) : @(kVK_F1),
        @(keycode_to_uint(keyboard::F2_KEY)) : @(kVK_F2),
        @(keycode_to_uint(keyboard::F3_KEY)) : @(kVK_F3),
        @(keycode_to_uint(keyboard::F4_KEY)) : @(kVK_F4),
        @(keycode_to_uint(keyboard::F5_KEY)) : @(kVK_F5),
        @(keycode_to_uint(keyboard::F6_KEY)) : @(kVK_F6),
        @(keycode_to_uint(keyboard::F7_KEY)) : @(kVK_F7),
        @(keycode_to_uint(keyboard::F8_KEY)) : @(kVK_F8),
        @(keycode_to_uint(keyboard::F9_KEY)) : @(kVK_F9),
        @(keycode_to_uint(keyboard::F10_KEY)) : @(kVK_F10),
        @(keycode_to_uint(keyboard::F11_KEY)) : @(kVK_F11),
        @(keycode_to_uint(keyboard::F12_KEY)) : @(kVK_F12),
        @(keycode_to_uint(keyboard::F13_KEY)) : @(kVK_F13),
        @(keycode_to_uint(keyboard::F14_KEY)) : @(kVK_F14),
        @(keycode_to_uint(keyboard::F15_KEY)) : @(kVK_F15),
        @(keycode_to_uint(keyboard::F16_KEY)) : @(kVK_F16),
        @(keycode_to_uint(keyboard::F17_KEY)) : @(kVK_F17),
        @(keycode_to_uint(keyboard::F18_KEY)) : @(kVK_F18),
        @(keycode_to_uint(keyboard::F19_KEY)) : @(kVK_F19),
        @(keycode_to_uint(keyboard::F20_KEY)) : @(kVK_F20)
    };
}

+(keycode) nativeCodeAsKeycode:(CGKeyCode)key {
    NSNumber* converted_key = @(key);
    NSDictionary<NSNumber*, NSNumber*>* key_map = [KeycodeConverter
                                                   fetchConversionMap];
    for (NSNumber* keycode_val in [key_map allKeys]) {
        if ([key_map[keycode_val] intValue] == [converted_key intValue]) {
            return uint_to_keycode((uint32_t) [keycode_val intValue]);
        }
    }
    return keycode::UNKNOWN_KEY;
}

+(CGKeyCode) keycodeAsNativeCode:(keycode)key {
    NSDictionary<NSNumber*, NSNumber*>* key_map = [KeycodeConverter
                                                   fetchConversionMap];
    NSNumber* converted_key = @(keycode_to_uint(key));
    return (CGKeyCode) [key_map[converted_key] unsignedIntValue];
}

@end
