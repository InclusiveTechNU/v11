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

#include <set>
#include <list>
#include "larkin/interaction/sound/text2speech/text2speech_synthesizer.h"

using sound::voice::Text2SpeechSynthesizer;

namespace sound {

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

};  // namespace sound
