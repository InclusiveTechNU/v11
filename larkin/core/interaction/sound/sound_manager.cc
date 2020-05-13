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

#include "interaction/sound/sound_manager.h"

namespace sound {
namespace voice {

SoundManager::SoundManager(const std::set<sound_type>& init_synth_types) :
                           activated_types(init_synth_types) {
    for (const sound_type& type : init_synth_types) {
        if (type == sound_type::TEXT2SPEECH) {
            t2s_synthesizer = new Text2SpeechSynthesizer;
        }
    }
}

const synth_container* SoundManager::get_sound_synth(const sound_type& type) {
    if (type == sound_type::TEXT2SPEECH) {
        synth_container* container = new synth_container{(sound_synth)
                                                         t2s_synthesizer,
                                                         TEXT2SPEECH};
        distributed_synth_ptrs.push_back(container);
        return container;
    }
    return nullptr;
}

const std::list<synth_container*> SoundManager::get_activated_synths() {
    std::list<synth_container*> activated_synths;

    for (const sound_type& type : activated_types) {
        if (type == sound_type::TEXT2SPEECH) {
            synth_container* container = new synth_container{(sound_synth)
                                                            t2s_synthesizer,
                                                            TEXT2SPEECH};
            distributed_synth_ptrs.push_back(container);
            activated_synths.push_back(container);
        }
    }

    return activated_synths;
}

const Text2SpeechSynthesizer* SoundManager::get_text2speech_synth() {
    return t2s_synthesizer;
}

SoundManager::~SoundManager() {
    for (synth_container* synth : distributed_synth_ptrs) {
        delete synth;
    }
    delete t2s_synthesizer;
}

};  // namespace voice
};  // namespace sound
