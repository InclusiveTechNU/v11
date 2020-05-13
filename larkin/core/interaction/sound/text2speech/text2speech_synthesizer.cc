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

#include <string.h>
#include "interaction/sound/text2speech/text2speech_synthesizer.h"
#include "utils/definitions.h"

namespace sound {
namespace voice {


Text2SpeechSynthesizer::Text2SpeechSynthesizer() {
    init_bridge();
}

Text2SpeechSynthesizer::Text2SpeechSynthesizer(Voice* default_voice) :
                                              default_voice(default_voice) {
    init_bridge();
}

void Text2SpeechSynthesizer::init_bridge() {
    bridge = new Text2SpeechSynthesizerBridge;
}

bool Text2SpeechSynthesizer::is_paused() {
    return paused;
}

void Text2SpeechSynthesizer::play_backlog() {
    while (speech_requests.size() > 0) {
        const speech_request& request = speech_requests.back();
        speak(request.text.c_str(), request.voice);
        speech_requests.pop_back();
    }
}

void Text2SpeechSynthesizer::set_paused(bool is_paused) {
    paused = is_paused;
    if (paused && !is_paused) {
        play_backlog();
    }
}

void Text2SpeechSynthesizer::pause() {
    set_paused(true);
}

void Text2SpeechSynthesizer::unpause() {
    set_paused(false);
}

const Voice* Text2SpeechSynthesizer::get_default_voice() {
    return default_voice;
}

void Text2SpeechSynthesizer::set_default_voice(Voice* voice) {
    default_voice = voice;
}

bool Text2SpeechSynthesizer::remove_speech_request(request_id id) {
    for (int i = 0; i < speech_requests.size(); i++) {
        const speech_request& request = speech_requests[i];
        if (request.id == id) {
            speech_requests.erase(speech_requests.begin() + i);
            return true;
        }
    }
    return false;
}

bool Text2SpeechSynthesizer::speak(const char* text,
                                   const Voice* voice) {
    speech_request request = {
        0,
        voice,
        text
    };

    // Non-system default voices are copied as the voice request
    if (!request.voice && default_voice) {
        Voice* voice = new_space(Voice);
        *voice = *default_voice;
        request.voice = voice;
    }

    // Handle request to either backlog or to system output
    if (paused) {
        speech_requests.push_back(request);
        return true;
    }
    return bridge->speak(request);
}

bool Text2SpeechSynthesizer::speak(const char* text) {
    return speak(text, nullptr);
}

Text2SpeechSynthesizer::~Text2SpeechSynthesizer() {
    delete default_voice;
    delete bridge;
}

};  // namespace voice
};  // namespace sound
