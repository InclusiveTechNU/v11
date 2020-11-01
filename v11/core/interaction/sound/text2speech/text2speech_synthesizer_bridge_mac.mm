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

#include <Foundation/Foundation.h>
#include <Cocoa/Cocoa.h>
#include "utils/definitions.h"
#include "core/interaction/sound/text2speech/text2speech_synthesizer_bridge.h"
#include "core/interaction/sound/text2speech/text2speech_delegate_mac.h"

namespace sound {
namespace voice {

Text2SpeechSynthesizerBridge::Text2SpeechSynthesizerBridge() {
    NSSpeechSynthesizer* ns_speech_synth = [[NSSpeechSynthesizer alloc]
                                                                 initWithVoice: nil];
    Text2SpeechDelegate* t2s_delegate = [[Text2SpeechDelegate alloc] init];
    [ns_speech_synth setDelegate: t2s_delegate];
    delegate = (__bridge_retained void*) t2s_delegate;
    synthesizer = (__bridge_retained native_t2s_synthesizer)
                  ns_speech_synth;
}

const bool& Text2SpeechSynthesizerBridge::get_has_spoken() {
    return has_spoken;
}

bool Text2SpeechSynthesizerBridge::speak(const speech_request& request) {
    // Convert speech request to native objects
    const char* request_speak = request.text.c_str();
    NSString* speaking_text = [NSString stringWithUTF8String:
                                        request_speak];

    // Send speech request to native object
    // Identify the requested speaking voice
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    set_current_voice(request.voice);

    if (!has_spoken) {
        has_spoken = true;
    }

    // Start speaking request
    [ns_speech_synth startSpeakingString:speaking_text];
    return true;
}

void Text2SpeechSynthesizerBridge::set_current_voice(const Voice* voice) {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                            synthesizer;
    NSSpeechSynthesizerVoiceName voice_name = nil;
    if (voice) {
        voice_name = [NSString stringWithUTF8String:voice->get_id()];
    }

    [ns_speech_synth setVoice:voice_name];
}

const Voice* Text2SpeechSynthesizerBridge::get_current_voice() {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                            synthesizer;
    NSSpeechSynthesizerVoiceName voice_name = [ns_speech_synth voice];
    const char* voice_name_raw = [voice_name UTF8String];
    return Voice::get_voice_by_id(voice_name_raw);
}

void Text2SpeechSynthesizerBridge::set_callback(std::function<void()>* callback) {
    Text2SpeechDelegate* t2s_delegate = (__bridge Text2SpeechDelegate*)
                                            delegate;
    [t2s_delegate attachDidFinishCallback:callback];
    callback_ = callback;
}

void Text2SpeechSynthesizerBridge::set_rate(double rate) {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    ns_speech_synth.rate = (float) rate;
}

const double Text2SpeechSynthesizerBridge::get_rate() {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    return (double) ns_speech_synth.rate;
}

void Text2SpeechSynthesizerBridge::set_volume(double volume) {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    ns_speech_synth.volume = (float) volume;
}

const double Text2SpeechSynthesizerBridge::get_volume() {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    return (double) ns_speech_synth.volume;
}

const bool Text2SpeechSynthesizerBridge::is_speaking() {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    return ns_speech_synth.speaking;
}

void Text2SpeechSynthesizerBridge::stop_speaking() {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    [ns_speech_synth stopSpeaking];
}

void Text2SpeechSynthesizerBridge::resume_speaking() {
    NSSpeechSynthesizer* ns_speech_synth = (__bridge NSSpeechSynthesizer*)
                                           synthesizer;
    [ns_speech_synth continueSpeaking];
}

Text2SpeechSynthesizerBridge::~Text2SpeechSynthesizerBridge() {
    delete callback_;
    __lk_unused__ (__bridge_transfer Text2SpeechDelegate*) delegate;
    __lk_unused__ (__bridge_transfer NSSpeechSynthesizer*) synthesizer;
}

}  // namespace voice
}  // namespace sound
