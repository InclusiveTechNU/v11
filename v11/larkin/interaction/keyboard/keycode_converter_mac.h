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

#pragma once

#include <Foundation/Foundation.h>
#include <QuartzCore/QuartzCore.h>
#include "larkin/interaction/keyboard/keycode.h"

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
