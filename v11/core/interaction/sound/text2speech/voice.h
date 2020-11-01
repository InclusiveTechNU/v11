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
#include "core/interaction/sound/text2speech/voice_quality.h"
#include "core/interaction/sound/text2speech/voice_bridge.h"

namespace sound {
namespace voice {

// Provides an abstracted cross platform for using
// and interacting with system voice objects
class Voice {
 private:
    // A bridge interface to the native voice object
    VoiceBridge* native_voice_bridge;

    // Transfers ownership of the voice bridge object
    // to the core voice object. Can only be called
    // using one of the voice static methods
    explicit Voice(VoiceBridge* voice_bridge);

 public:
    // Return a vector of voice pointers supported by the system.
    // * Highly Recommended: pointer ownership to be transfered
    // * to the caller.
    static std::vector<const Voice*> get_system_voices();

    // Returns a pointer to a voice using a voice bridge
    // name for the voice. Returns null if the voice does not exist.
    // * Pointer ownership is transferred to the caller
    static const Voice* get_voice_by_id(const char* name);

    // Return the pointer to the default voice on the system. Returns null
    // if no system default exists.
    // * Pointer ownership is transferred to the caller
    static const Voice* get_default_voice();

    const char* get_id() const;

    const char* get_name() const;

    int get_age() const;

    const char* get_gender() const;

    const char* get_locale() const;

    const voice_quality get_quality() const;

    // Deletes the voice bridge object
    ~Voice();
};

}  // namespace voice
}  // namespace sound
