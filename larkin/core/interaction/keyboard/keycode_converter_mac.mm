/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <Carbon/Carbon.h>
#include "interaction/keyboard/keycode_converter_mac.h"

using keyboard::keycode;

@implementation KeycodeConverter

+(NSDictionary<NSNumber*, NSNumber*>*) fetchConversionMap {
    return @{
        @(keyboard::NUM_0_KEY) : @(kVK_ANSI_0),
        @(keyboard::NUM_1_KEY) : @(kVK_ANSI_1),
        @(keyboard::NUM_2_KEY) : @(kVK_ANSI_2),
        @(keyboard::NUM_3_KEY) : @(kVK_ANSI_3),
        @(keyboard::NUM_4_KEY) : @(kVK_ANSI_4),
        @(keyboard::NUM_5_KEY) : @(kVK_ANSI_5),
        @(keyboard::NUM_6_KEY) : @(kVK_ANSI_6),
        @(keyboard::NUM_7_KEY) : @(kVK_ANSI_7),
        @(keyboard::NUM_8_KEY) : @(kVK_ANSI_8),
        @(keyboard::NUM_9_KEY) : @(kVK_ANSI_9),

        @(keyboard::A_KEY) : @(kVK_ANSI_A),
        @(keyboard::S_KEY) : @(kVK_ANSI_S),
        @(keyboard::D_KEY) : @(kVK_ANSI_D),
        @(keyboard::F_KEY) : @(kVK_ANSI_F),
        @(keyboard::H_KEY) : @(kVK_ANSI_H),
        @(keyboard::G_KEY) : @(kVK_ANSI_G),
        @(keyboard::Z_KEY) : @(kVK_ANSI_Z),
        @(keyboard::X_KEY) : @(kVK_ANSI_X),
        @(keyboard::C_KEY) : @(kVK_ANSI_C),
        @(keyboard::V_KEY) : @(kVK_ANSI_V),
        @(keyboard::B_KEY) : @(kVK_ANSI_B),
        @(keyboard::Q_KEY) : @(kVK_ANSI_Q),
        @(keyboard::W_KEY) : @(kVK_ANSI_W),
        @(keyboard::E_KEY) : @(kVK_ANSI_E),
        @(keyboard::R_KEY) : @(kVK_ANSI_R),
        @(keyboard::Y_KEY) : @(kVK_ANSI_Y),
        @(keyboard::T_KEY) : @(kVK_ANSI_T),
        @(keyboard::O_KEY) : @(kVK_ANSI_O),
        @(keyboard::U_KEY) : @(kVK_ANSI_U),
        @(keyboard::I_KEY) : @(kVK_ANSI_I),
        @(keyboard::P_KEY) : @(kVK_ANSI_P),
        @(keyboard::L_KEY) : @(kVK_ANSI_L),
        @(keyboard::J_KEY) : @(kVK_ANSI_J),
        @(keyboard::K_KEY) : @(kVK_ANSI_K),
        @(keyboard::M_KEY) : @(kVK_ANSI_M),
        @(keyboard::N_KEY) : @(kVK_ANSI_N),

        @(keyboard::MINUS_KEY) : @(kVK_ANSI_Minus),
        @(keyboard::EQUAL_KEY) : @(kVK_ANSI_Equal),

        @(keyboard::RIGHT_BRACKET_KEY) : @(kVK_ANSI_RightBracket),
        @(keyboard::LEFT_BRACKET_KEY) : @(kVK_ANSI_LeftBracket),

        @(keyboard::QUOTE_KEY) : @(kVK_ANSI_Quote),
        @(keyboard::SEMICOLON_KEY) : @(kVK_ANSI_Semicolon),
        @(keyboard::BACKSLASH_KEY) : @(kVK_ANSI_Backslash),
        @(keyboard::COMMA_KEY) : @(kVK_ANSI_Comma),
        @(keyboard::PERIOD_KEY) : @(kVK_ANSI_Period),
        @(keyboard::SLASH_KEY) : @(kVK_ANSI_Slash),
        @(keyboard::GRAVE_KEY) : @(kVK_ANSI_Grave),

        @(keyboard::RETURN_KEY) : @(kVK_Return),
        @(keyboard::TAB_KEY) : @(kVK_Tab),

        @(keyboard::SPACE_KEY) : @(kVK_Space),
        @(keyboard::DELETE_KEY) : @(kVK_Delete),
        @(keyboard::FORWARD_DELETE_KEY) : @(kVK_ForwardDelete),

        @(keyboard::ESCAPE_KEY) : @(kVK_Escape),
        @(keyboard::COMMAND_KEY) : @(kVK_Command),
        @(keyboard::SHIFT_LEFT_KEY) : @(kVK_Shift),
        @(keyboard::CAPSLOCK_KEY) : @(kVK_CapsLock),
        @(keyboard::OPTION_LEFT_KEY) : @(kVK_Option),
        @(keyboard::CONTROL_LEFT_KEY) : @(kVK_Control),
        @(keyboard::SHIFT_RIGHT_KEY) : @(kVK_RightShift),
        @(keyboard::OPTION_RIGHT_KEY) : @(kVK_RightOption),
        @(keyboard::CONTROL_RIGHT_KEY) : @(kVK_RightControl),
        @(keyboard::END_KEY) : @(kVK_End),

        @(keyboard::VOLUME_UP_KEY) : @(kVK_VolumeUp),
        @(keyboard::VOLUME_DOWN_KEY) : @(kVK_VolumeDown),
        @(keyboard::VOLUME_MUTE_KEY) : @(kVK_Mute),

        @(keyboard::HELP_KEY) : @(kVK_Help),
        @(keyboard::HOME_KEY) : @(kVK_Home),

        @(keyboard::PAGE_UP_KEY) : @(kVK_PageUp),
        @(keyboard::PAGE_DOWN_KEY) : @(kVK_PageDown),

        @(keyboard::LEFT_ARROW_KEY) : @(kVK_LeftArrow),
        @(keyboard::RIGHT_ARROW_KEY) : @(kVK_RightArrow),
        @(keyboard::DOWN_ARROW_KEY) : @(kVK_DownArrow),
        @(keyboard::UP_ARROW_KEY) : @(kVK_UpArrow),

        @(keyboard::KEYPAD_NUM_0_KEY) : @(kVK_ANSI_Keypad0),
        @(keyboard::KEYPAD_NUM_1_KEY) : @(kVK_ANSI_Keypad1),
        @(keyboard::KEYPAD_NUM_2_KEY) : @(kVK_ANSI_Keypad2),
        @(keyboard::KEYPAD_NUM_3_KEY) : @(kVK_ANSI_Keypad3),
        @(keyboard::KEYPAD_NUM_4_KEY) : @(kVK_ANSI_Keypad4),
        @(keyboard::KEYPAD_NUM_5_KEY) : @(kVK_ANSI_Keypad5),
        @(keyboard::KEYPAD_NUM_6_KEY) : @(kVK_ANSI_Keypad6),
        @(keyboard::KEYPAD_NUM_7_KEY) : @(kVK_ANSI_Keypad7),
        @(keyboard::KEYPAD_NUM_8_KEY) : @(kVK_ANSI_Keypad8),
        @(keyboard::KEYPAD_NUM_9_KEY) : @(kVK_ANSI_Keypad9),
        @(keyboard::KEYPAD_DECIMAL_KEY) : @(kVK_ANSI_KeypadDecimal),
        @(keyboard::KEYPAD_MULTIPLY_KEY) : @(kVK_ANSI_KeypadMultiply),
        @(keyboard::KEYPAD_PLUS_KEY) : @(kVK_ANSI_KeypadPlus),
        @(keyboard::KEYPAD_CLEAR_KEY) : @(kVK_ANSI_KeypadClear),
        @(keyboard::KEYPAD_DIVIDE_KEY) : @(kVK_ANSI_KeypadDivide),
        @(keyboard::KEYPAD_ENTER_KEY) : @(kVK_ANSI_KeypadEnter),
        @(keyboard::KEYPAD_MINUS_KEY) : @(kVK_ANSI_KeypadMinus),
        @(keyboard::KEYPAD_EQUALS_KEY) : @(kVK_ANSI_KeypadEquals),

        @(keyboard::FUNCTION_KEY) : @(kVK_Function),
        @(keyboard::F1_KEY) : @(kVK_F1),
        @(keyboard::F2_KEY) : @(kVK_F2),
        @(keyboard::F3_KEY) : @(kVK_F3),
        @(keyboard::F4_KEY) : @(kVK_F4),
        @(keyboard::F5_KEY) : @(kVK_F5),
        @(keyboard::F6_KEY) : @(kVK_F6),
        @(keyboard::F7_KEY) : @(kVK_F7),
        @(keyboard::F8_KEY) : @(kVK_F8),
        @(keyboard::F9_KEY) : @(kVK_F9),
        @(keyboard::F10_KEY) : @(kVK_F10),
        @(keyboard::F11_KEY) : @(kVK_F11),
        @(keyboard::F12_KEY) : @(kVK_F12),
        @(keyboard::F13_KEY) : @(kVK_F13),
        @(keyboard::F14_KEY) : @(kVK_F14),
        @(keyboard::F15_KEY) : @(kVK_F15),
        @(keyboard::F16_KEY) : @(kVK_F16),
        @(keyboard::F17_KEY) : @(kVK_F17),
        @(keyboard::F18_KEY) : @(kVK_F18),
        @(keyboard::F19_KEY) : @(kVK_F19),
        @(keyboard::F20_KEY) : @(kVK_F20)
    };
}

+(keycode) nativeCodeAsKeycode:(CGKeyCode)key {
    NSNumber* converted_key = @(key);
    NSDictionary<NSNumber*, NSNumber*>* key_map = [KeycodeConverter
                                                   fetchConversionMap];
    for (NSNumber* keycode_val in key_map) {
        NSNumber* native_code = key_map[keycode_val];
        if (converted_key == native_code)
            return (keycode) [keycode_val intValue];
    }
    return keycode::NUM_0_KEY;
}

+(CGKeyCode) keycodeAsNativeCode:(keycode)key {
    NSDictionary<NSNumber*, NSNumber*>* key_map = [KeycodeConverter
                                                   fetchConversionMap];
    NSNumber* converted_key = @(key);
    return (CGKeyCode) [key_map[converted_key] unsignedIntValue];
}

@end
