/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include <string.h>
#include <iostream>
#include "utils/definitions.h"
#include "interaction/sound/text2speech/voice_bridge.h"

namespace sound {
namespace voice {

typedef NSSpeechSynthesizerVoiceName VoiceName;
typedef NSVoiceAttributeKey VoiceKey;

VoiceBridge::VoiceBridge(native_voice voice_ptr) {
    VoiceName voice_name = (__bridge_transfer VoiceName) voice_ptr;
    // TODO(tommymchugh): Silence nslog stdout when no voice exists
    NSDictionary<VoiceKey, id>* voice_attrs = [NSSpeechSynthesizer
                                               attributesForVoice:voice_name];
    if ([voice_attrs count] > 0) {
        native_voice_ptr = (__bridge_retained native_voice) voice_attrs;
    } else {
        voice_exists_ = false;
    }
}

std::vector<VoiceBridge*> VoiceBridge::get_native_voice_bridges() {
    std::vector<VoiceBridge*> system_vbs;
    NSArray<VoiceName>* voices = [NSSpeechSynthesizer availableVoices];
    for (int i = 0; i < [voices count]; i++) {
        VoiceName voice = voices[i];
        native_voice voice_ptr = (__bridge_retained native_voice) voice;
        VoiceBridge* vb = new VoiceBridge(voice_ptr);
        system_vbs.push_back(vb);
    }
    return system_vbs;
}

VoiceBridge* VoiceBridge::get_native_voice_by_id(const char* name) {
    if (!name) {
        return nullptr;
    }
    VoiceName voice_name_str = [NSString stringWithUTF8String:name];
    native_voice voice_ptr = (__bridge_retained native_voice) voice_name_str;
    VoiceBridge* vb_with_id = new VoiceBridge(voice_ptr);
    if (!vb_with_id->exists()) {
        delete vb_with_id;
        vb_with_id = nullptr;
    }
    return vb_with_id;
}

VoiceBridge* VoiceBridge::get_native_default_voice() {
    VoiceName default_voice = [NSSpeechSynthesizer defaultVoice];
    native_voice voice_ptr = (__bridge_retained native_voice) default_voice;

    VoiceBridge* voice_bridge = new VoiceBridge(voice_ptr);
    if (!voice_bridge->exists()) {
        delete voice_bridge;
        voice_bridge = nullptr;
    }
    return voice_bridge;
}

bool VoiceBridge::exists() {
    return voice_exists_;
}

const char* VoiceBridge::get_id() {
    if (!exists()) {
        return nullptr;
    }

    NSDictionary<VoiceKey, id>* voice_attrs = (__bridge
                                              NSDictionary<VoiceKey, id>*)
                                              native_voice_ptr;
    NSString* voice_id = voice_attrs[NSVoiceIdentifier];
    return [voice_id UTF8String];
}

const char* VoiceBridge::get_name() {
    if (!exists()) {
        return nullptr;
    }

    NSDictionary<VoiceKey, id>* voice_attrs = (__bridge
                                              NSDictionary<VoiceKey, id>*)
                                              native_voice_ptr;
    NSString* voice_name = voice_attrs[NSVoiceName];
    return [voice_name UTF8String];
}

const char* VoiceBridge::get_age() {
    if (!exists()) {
        return nullptr;
    }

    NSDictionary<VoiceKey, id>* voice_attrs = (__bridge
                                              NSDictionary<VoiceKey, id>*)
                                              native_voice_ptr;
    NSString* voice_age = voice_attrs[NSVoiceAge];
    return [voice_age UTF8String];
}

const char* VoiceBridge::get_gender() {
    if (!exists()) {
        return nullptr;
    }

    NSDictionary<VoiceKey, id>* voice_attrs = (__bridge
                                              NSDictionary<VoiceKey, id>*)
                                              native_voice_ptr;
    NSString* voice_gender = voice_attrs[NSVoiceGender];
    return [voice_gender UTF8String];
}

const char* VoiceBridge::get_locale() {
    if (!exists()) {
        return nullptr;
    }

    NSDictionary<VoiceKey, id>* voice_attrs = (__bridge
                                              NSDictionary<VoiceKey, id>*)
                                              native_voice_ptr;
    NSString* voice_locale = voice_attrs[NSVoiceLocaleIdentifier];
    return [voice_locale UTF8String];
}

const voice_quality VoiceBridge::get_quality() {
    // TODO(tommymchugh): Check for more types
    // See voice_quality.h
    return voice_quality::DEFAULT;
}

VoiceBridge::~VoiceBridge() {
    __unused__ (__bridge_transfer NSDictionary<VoiceKey, id>*)
                native_voice_ptr;
}

};  // namespace voice
};  // namespace sound
