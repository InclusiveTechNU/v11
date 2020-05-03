/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <set>
#include <list>
#include "interaction/sound/text2speech/text2speech_synthesizer.h"

namespace sound {
namespace voice {

enum sound_type {
    TEXT2SPEECH
};

typedef void* sound_synth;

struct synth_container {
    const sound_synth synth;
    const sound_type type;
};

class SoundManager {
 private:
    std::set<sound_type> activated_types;
    Text2SpeechSynthesizer* t2s_synthesizer = nullptr;
    std::list<synth_container*> distributed_synth_ptrs;

 public:
    explicit SoundManager(const std::set<sound_type>& init_synth_types);
    const synth_container* get_sound_synth(const sound_type& type);
    const std::list<synth_container*> get_activated_synths();
    const Text2SpeechSynthesizer* get_text2speech_synth();
    ~SoundManager();
};

};  // namespace voice
};  // namespace sound
