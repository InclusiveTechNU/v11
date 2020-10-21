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

#include <functional>
#include "larkin/interaction/sound/text2speech/voice.h"
#include "larkin/interaction/sound/text2speech/speech_request.h"

namespace sound {
namespace voice {

typedef void* native_t2s_synthesizer;

class Text2SpeechSynthesizerBridge {
 private:
    // The pointer to the native system synthesizer
    // This is owned until the bridge is destroyed
    // when it is released back to the native memory
    // management system
    native_t2s_synthesizer synthesizer;
    void* delegate = nullptr;
    std::function<void()>* callback_ = nullptr;

    // Marks if a user has spoken yet. May be used
    // on some platforms for marking whether the synthesis
    // of the text is within an existing context
    bool has_spoken = false;

 public:
    // Transfers ownership of a system synthesizer object
    // to the synthesizer bridge
    Text2SpeechSynthesizerBridge();

    // Sends a speech request to be spoken by the native
    // system synthesizer
    bool speak(const speech_request& request);

    // Returns whether the native system synthesizer object
    // has spoken yet
    const bool& get_has_spoken();

    void set_current_voice(const Voice* voice);
    const Voice* get_current_voice();
    void set_rate(double rate);
    const double get_rate();
    void set_volume(double volume);
    const double get_volume();
    const bool is_speaking();
    void stop_speaking();
    void resume_speaking();
    void set_callback(std::function<void()>* callback);


    // Transfers ownership of the native system synthesizer
    // object back to the native memory management system
    ~Text2SpeechSynthesizerBridge();
};

}  // namespace voice
}  // namespace sound
