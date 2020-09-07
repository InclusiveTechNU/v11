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

#include <vector>
#include <string>
#include "larkin/interaction/sound/text2speech/speech_request.h"
#include "larkin/interaction/sound/text2speech/text2speech_synthesizer_bridge.h"

namespace sound {
namespace voice {

class Text2SpeechSynthesizer {
 private:
    // Interface to the native text to speech synthesizer
    Text2SpeechSynthesizerBridge* bridge;

    // Controls whether the synthesizer should play a request
    // that is submitted to the synthesizer
    bool paused = false;

    // The default voice used for speech synthesis. If null
    // the voice defaults to the system default voice
    Voice* default_voice = nullptr;

    // A backlog of speech requests that are called synchronously
    // And will restart at pausing point if the synthesizer is paused
    std::vector<speech_request> speech_requests;

    // Initialize the native system bridge object
    void init_bridge();

    // Plays all back log speech requests. Traditionally
    // used after a synthesizer is unpaused
    void play_backlog();

 public:
    // Allocates system instances for speech synthesis
    Text2SpeechSynthesizer();

    // Allocates system instances for speech synthesis
    // and sets the value for the default voice
    explicit Text2SpeechSynthesizer(Voice* default_voice);

    // Returns whether the synthesizer is paused
    bool is_paused();

    // Sets whether the synthesizer is paused
    void set_paused(bool is_paused);

    // Pauses the synthesizer if it is unpaused.
    // Syntactic sugar for set_paused(true);
    void pause();

    // Unpauses the synthesizer if it is paused.
    // Syntactic sugar for set_paused(false);
    void unpause();

    // Returns the default voice set for this synthesizer.
    // When the default voice is unset, will return a pointer
    // to the system default voice.
    const Voice* get_default_voice();

    // Changes the default voice used for the synthesizer.
    // If set to null will return to the system default.
    // The default voice is used when a speech request is submitted
    // with a null pointer for the voice.
    // `voice` will not be owned by the synthesizer and must remain
    // in memory for the existance of the synthesizer.
    void set_default_voice(Voice* voice);

    // Removes a speech request from the request pool
    // if the request exists. Will return true if the request
    // was found and removed. Otherwise, will return false if
    // request_id was not found
    bool remove_speech_request(request_id id);

    bool speak(const char* text, const Voice* voice);

    bool speak(const char* text);

    // Deallocates the native memory objects
    ~Text2SpeechSynthesizer();
};

};  // namespace voice
};  // namespace sound
