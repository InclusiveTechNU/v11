/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <Foundation/Foundation.h>
#include <QuartzCore/QuartzCore.h>
#include "interaction/keyboard/keycode.h"

using keyboard::keycode;

// The larkin2native and native2larkin keycode converter
// for the mac system.
// ! All methods are STATIC
@interface KeycodeConverter : NSObject

// Returns a dictionary with larkin 2 native keys.
// Keys are larkin keycodes and values are Carbon event values
+(NSDictionary<NSNumber*, NSNumber*>*) fetchConversionMap;

// Returns a larkin keycode from a native keycode
+(keycode) nativeCodeAsKeycode:(CGKeyCode)key;

// Returns a native keycode from a larkin keycode
+(CGKeyCode) keycodeAsNativeCode:(keycode)key;

@end
