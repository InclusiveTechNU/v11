/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
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
