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

#include <functional>
#include <vector>
#include "client/node/interaction.h"
#include "core/interaction/sound/text2speech/voice.h"

using sound::voice::Voice;

namespace interaction {

napi_status sound(napi_env env, napi_value exports) {
    napi_status status;

    // *****************************
    // *  Speech API Interface
    // *****************************
    napi_value speech;
    status = napi_create_object(env, &speech);
    if (status != napi_ok) return status;

    // * speech.getVoices() -> Array<Object>
    // Returns a list of system voices as Voice class objects
    napi_value get_sys_voices;
    status = napi_create_function(env,
                                  nullptr,
                                  0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        napi_status status;
        napi_value system_voices;
        status = napi_create_array(env, &system_voices);
        if (status != napi_ok) return nullptr;

        // Fill system voices with mapped Voice class to JS Object
        static const Voice* voice = Voice::get_default_voice();
        /*for (size_t i = 0; i < voices.size(); i++) {
            const Voice* voice = voices[i];
            delete voice;
        }*/

        return system_voices;
    }, nullptr, &get_sys_voices);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env,
                                     speech,
                                     "getVoices",
                                     get_sys_voices);
    if (status != napi_ok) return status;

    // Declare and place speech api binding within v11.speech
    status = napi_set_named_property(env, exports, "speech", speech);
    if (status != napi_ok) return status;
    return status;
}

// Initialize all variables and functions
void init(napi_env env, napi_value exports) {
    napi_status sound_status = sound(env, exports);
    if (sound_status != napi_ok) {
        napi_throw_error(env,
                         nullptr,
                         "Failed to initialize interaction/sound");
        return;
    }
}

};  // namespace interaction
