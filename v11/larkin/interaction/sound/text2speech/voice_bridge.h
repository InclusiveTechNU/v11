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
#include "larkin/interaction/sound/text2speech/voice_quality.h"

namespace sound {
namespace voice {

// TODO(tommymchugh): Implement get_native_voice_with_language
// See: https://developer.apple.com/documentation/avfoundation/
//      avspeechsynthesisvoice/1619699-voicewithlanguage

// A pointer to a native system voice whose ownership
// has been transferred to the caller from the native
// memory management system (such as ARC)
typedef void* native_voice;

// Provides an interface to manage the native voice
// object such as retrieve information and perform
// actions using the native object
class VoiceBridge {
 private:
    bool voice_exists_ = true;

    // The owned voice native object
    native_voice native_voice_ptr;

    // Transfers ownership of the native_voice
    // to the voice bridge object. Can only be called
    // using one of the voice bridge static methods
    explicit VoiceBridge(native_voice voice_ptr);

 public:
    // Return a vector of native voices pointers supported by the system.
    // To be used to send all native voices to Larkin voice objects.
    // * Highly Recommended: pointer ownership to be transfered
    // * to the caller.
    static std::vector<VoiceBridge*> get_native_voice_bridges();

    // Returns a pointer to a voice bridge using the native system
    // name for the voice. Returns null if the voice does not exist.
    // * Pointer ownership is transferred to the caller
    static VoiceBridge* get_native_voice_by_name(const char* name);

    // Returns a pointer to a voice bridge using the native system
    // id for the voice. Returns null if the voice does not exist.
    // * Pointer ownership is transferred to the caller
    // ! This method is slow. Prefered to use get_native_voice_by_name
    static VoiceBridge* get_native_voice_by_id(const char* voice_id);

    // Return the pointer to the default native voice. Returns null
    // if no system default exists.
    // * Pointer ownership is transferred to the caller
    static VoiceBridge* get_native_default_voice();

    const char* get_id();

    const char* get_name();

    int get_age();

    const char* get_gender();

    const char* get_locale();

    bool exists();

    const voice_quality get_quality();

    // Returns the native voice to the system memory management
    // system
    ~VoiceBridge();
};

}  // namespace voice
}  // namespace sound
