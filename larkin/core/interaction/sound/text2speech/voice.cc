/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "interaction/sound/text2speech/voice.h"
#include "utils/string.h"

namespace sound {
namespace voice {

using utils::string_copy;

Voice::Voice(VoiceBridge* voice_bridge) : native_voice_bridge(voice_bridge) {}

std::vector<const Voice*> Voice::get_system_voices() {
    std::vector<const Voice*> voices;
    std::vector<VoiceBridge*> system_vbs = VoiceBridge::
                                           get_native_voice_bridges();
    for (VoiceBridge*& voice_bridge : system_vbs) {
        Voice* voice = new Voice(voice_bridge);
        voices.push_back(voice);
    }

    return voices;
}

const Voice* Voice::get_voice_by_id(const char* name) {
    VoiceBridge* vb_with_name = VoiceBridge::get_native_voice_by_id(name);
    if (!vb_with_name) {
        return nullptr;
    }

    Voice* voice = new Voice(vb_with_name);
    return voice;
}

const Voice* Voice::get_default_voice() {
    VoiceBridge* default_vb = VoiceBridge::get_native_default_voice();
    if (!default_vb) {
        return nullptr;
    }
    Voice* voice = new Voice(default_vb);
    return voice;
}

const char* Voice::get_name() const {
    return string_copy(native_voice_bridge->get_name());
}

const char* Voice::get_id() const {
    return string_copy(native_voice_bridge->get_id());
}

const char* Voice::get_age() const {
    return string_copy(native_voice_bridge->get_age());
}

const char* Voice::get_gender() const {
    return string_copy(native_voice_bridge->get_gender());
}

const char* Voice::get_locale() const {
    return string_copy(native_voice_bridge->get_locale());
}

const voice_quality Voice::get_quality() const {
    return native_voice_bridge->get_quality();
}

Voice::~Voice() {
    delete native_voice_bridge;
}

};  // namespace voice
};  // namespace sound
