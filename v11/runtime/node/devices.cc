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
#include <string>
#include "runtime/node/devices.h"
#include "runtime/node/sound_utils.h"
#include "runtime/node/utils.h"
#include "core/system/system_instance.h"
#include "core/system/system.h"
#include "core/devices/sound/text2speech/voice.h"
#include "core/devices/sound/text2speech/text2speech_synthesizer.h"
#include "core/devices/sound/text2speech/text2speech_synthesizer_bridge.h"
#include "core/devices/keyboard/keyboard_simulator.h"
#include "core/devices/keyboard/keyboard_listener.h"
#include "core/devices/keyboard/keyboard_event.h"
#include "core/devices/keyboard/keycode.h"

using utils::string_from_value;
using utils::keyboard_event_to_object;
using keyboard::keycode;
using keyboard::KeyboardSimulator;
using sound::voice::Text2SpeechSynthesizer;
using sound::voice::Text2SpeechSynthesizerBridge;
using sound::voice::Voice;
using sound::voice::SpeechDidFinishCallback;
using keyboard::KeyboardListener;
using keyboard::event::event_type;
using keyboard::event::KeyboardEvent;
using devices::utils::sound::voice_to_object;
using sys::SystemInstance;
using sys::System;

namespace devices {

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
        std::vector<const Voice*> sys_voices = Voice::get_system_voices();
        for (size_t i = 0; i < sys_voices.size(); i++) {
             // Create voice object and set to index of i
            const Voice* voice = sys_voices[i];
            napi_value voice_object;
            status = napi_create_object(env, &voice_object);
            if (status != napi_ok) return nullptr;

            status = voice_to_object(env, voice, voice_object);
            if (status != napi_ok) return nullptr;
            status = napi_set_element(env, system_voices, i, voice_object);
            if (status != napi_ok) return nullptr;
            delete voice;
        }

        return system_voices;
    }, nullptr, &get_sys_voices);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env,
                                     speech,
                                     "getVoices",
                                     get_sys_voices);
    if (status != napi_ok) return status;

    // * speech.getDefaultVoice() -> Object
    // Returns the default voice object of the system
    napi_value get_default_voice;
    status = napi_create_function(env,
                                  nullptr,
                                  0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        // Create a voice object from the default native system voice
        napi_status status;
        napi_value system_voice_object;
        const Voice* sys_voice = Voice::get_default_voice();

        status = napi_create_object(env, &system_voice_object);
        if (status != napi_ok) return nullptr;
        status = voice_to_object(env, sys_voice, system_voice_object);

        delete sys_voice;
        return system_voice_object;
    }, nullptr, &get_default_voice);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env,
                                     speech,
                                     "getDefaultVoice",
                                     get_default_voice);
    if (status != napi_ok) return status;

    // * speech.speak(text: string, voice_id: string) -> void
    // Calls the native speach synthesis API with the specific voice declared
    napi_value speak;
    status = napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        // TODO(tommymchugh): Evoke error on failed to collect arguments
        napi_status status;
        // Collect text and voice_id from info
        size_t args_count = 3;
        napi_value args[3];
        status = napi_get_cb_info(env, info, &args_count, args, nullptr, 0);
        if (status != napi_ok) return nullptr;

        napi_value text_object = args[0];
        napi_value voice_id_object = args[1];
        char* text_ptr = string_from_value(env, text_object);
        char* voice_id_ptr = string_from_value(env, voice_id_object);
        if (!text_ptr || !voice_id_ptr) return nullptr;

        // TODO(tommymchugh): Figure out how to check for null for callback
        // Create async thread-safe callback function
        // Handle the threadsafe call by sending Notification into callback
        typedef napi_threadsafe_function_call_js ts_callback;
        ts_callback speech_cb = [](napi_env env,
                                   napi_value js_cb,
                                   void* context,
                                   void* data) {
            napi_value undefined;
            a_ok(napi_get_undefined(env, &undefined));
            a_ok(napi_call_function(env,
                                    undefined,
                                    js_cb,
                                    0, nullptr,
                                    nullptr));
        };
        napi_value listener_callback_object = args[2];
        napi_threadsafe_function listener_callback;
        napi_value res_name;
        napi_create_string_utf8(env, "resource", NAPI_AUTO_LENGTH, &res_name);
        if (status != napi_ok) return nullptr;
        status = napi_create_threadsafe_function(env, listener_callback_object,
                                                 nullptr, res_name,
                                                 0, 2,
                                                 nullptr, nullptr, nullptr,
                                                 speech_cb,
                                                 &listener_callback);
        if (status != napi_ok) return nullptr;

        // Send speech request to the native core interface
        const Voice* speaking_voice = Voice::get_voice_by_id(voice_id_ptr);
        if (speaking_voice != nullptr) {
            Text2SpeechSynthesizer* speech_synth =
                new Text2SpeechSynthesizer();
           Text2SpeechSynthesizerBridge* speech_bridge = speech_synth->
                                                          get_bridge();
            /* SpeechDidFinishCallback* speech_callback =
                new SpeechDidFinishCallback([&]() {
                    napi_acquire_threadsafe_function(listener_callback);
                    napi_call_threadsafe_function(listener_callback,
                                                nullptr,
                                                napi_tsfn_blocking);
                    delete speaking_voice;
                    delete speech_synth;
                });
            speech_bridge->set_callback(speech_callback);*/
            speech_synth->speak(text_ptr, speaking_voice);
        } else {
            // TODO(tommymchugh): throw error for no speaking
        }
        return nullptr;
    }, nullptr, &speak);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env, speech, "speak", speak);
    if (status != napi_ok) return status;

    // Declare and place speech api binding within v11.speech
    status = napi_set_named_property(env, exports, "speech", speech);
    if (status != napi_ok) return status;
    return status;
}

napi_status keyboard(napi_env env, napi_value exports) {
    napi_status status;
    napi_value keyboard;
    status = napi_create_object(env, &keyboard);
    if (status != napi_ok) return status;

    // *****************************
    // *  KEY SIM API Interface
    // *****************************
    napi_value simulate;
    status = napi_create_object(env, &simulate);
    if (status != napi_ok) return status;

    napi_value hold_key;
    status = napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        // TODO(tommymchugh): Evoke error on failed to collect arguments
        napi_status status;
        // Collect character to hold
        size_t args_count = 1;
        napi_value args[1];
        status = napi_get_cb_info(env, info, &args_count, args, nullptr, 0);
        if (status != napi_ok) return nullptr;

        napi_value key_to_press_obj = args[0];
        int32_t key_code = 0;
        a_ok(napi_get_value_int32(env, key_to_press_obj, &key_code));
        uint32_t conv_key_code = (uint32_t) key_code;
        KeyboardSimulator simulator = KeyboardSimulator();
        simulator.press_key(keyboard::uint_to_keycode(conv_key_code));
        return nullptr;
    }, nullptr, &hold_key);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env, simulate, "holdKey", hold_key);
    if (status != napi_ok) return status;

    napi_value release_key;
    status = napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        // TODO(tommymchugh): Evoke error on failed to collect arguments
        napi_status status;
        // Collect character to release
        size_t args_count = 1;
        napi_value args[1];
        status = napi_get_cb_info(env, info, &args_count, args, nullptr, 0);
        if (status != napi_ok) return nullptr;

        napi_value key_to_press_obj = args[0];
        int32_t key_code = 0;
        a_ok(napi_get_value_int32(env, key_to_press_obj, &key_code));
        uint32_t conv_key_code = (uint32_t) key_code;
        KeyboardSimulator simulator = KeyboardSimulator();
        simulator.release_key(keyboard::uint_to_keycode(conv_key_code));
        return nullptr;
    }, nullptr, &release_key);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env, simulate, "releaseKey", release_key);
    if (status != napi_ok) return status;

    status = napi_set_named_property(env, keyboard, "simulation", simulate);
    if (status != napi_ok) return status;

    // *****************************
    // *  KEY LISTENER API Interface
    // *****************************
    napi_value listener_key;
    status = napi_create_function(env, nullptr, 0,
                                  [](napi_env env,
                                     napi_callback_info info) -> napi_value {
        // Retrieve sys_ptr data
        napi_status status;
        void* sys_void_ptr = nullptr;
        napi_get_cb_info(env, info, nullptr, nullptr, nullptr, &sys_void_ptr);
        if (!sys_void_ptr) {
            // TODO(tommymchugh): Faill on system pointer cannot be found
            return nullptr;
        }
        System* sys_ptr = reinterpret_cast<System*>(sys_void_ptr);
        // TODO(tommymchugh): Manage through system devices api
        KeyboardListener* keyboard_listener = new KeyboardListener;

        // TODO(tommymchugh): Evoke error on failed to collect arguments
        // Collect text and voice_id from info
        size_t args_count = 2;
        napi_value args[2];
        status = napi_get_cb_info(env, info, &args_count, args, nullptr, 0);
        if (status != napi_ok) return nullptr;

        napi_value listener_type_object = args[0];
        char* listener_type_ptr = string_from_value(env, listener_type_object);
        std::string listener_type_str = std::string(listener_type_ptr);
        delete listener_type_ptr;
        // TODO(tommymchugh): Figure out how to check for null for callback
        // Create async thread-safe callback function
        // Handle the threadsafe call by sending Notification into callback
        typedef napi_threadsafe_function_call_js ts_callback;
        ts_callback notification_cb = [](napi_env env,
                                         napi_value js_cb,
                                         void* context,
                                         void* data) {
            // Convert data to KeyboardEvent type
            KeyboardEvent* event = reinterpret_cast<KeyboardEvent*>(data);

            // TODO(tommymchugh): determine proper context not undef
            napi_value undefined, event_object;
            keyboard_event_to_object(env, event, &event_object);
            a_ok(napi_get_undefined(env, &undefined));
            a_ok(napi_call_function(env,
                                    undefined,
                                    js_cb,
                                    1, &event_object,
                                    nullptr));
            delete event;
        };

        napi_value listener_callback_object = args[1];
        napi_threadsafe_function listener_callback;
        napi_value res_name;
        napi_create_string_utf8(env, "resource", NAPI_AUTO_LENGTH, &res_name);
        if (status != napi_ok) return nullptr;

        status = napi_create_threadsafe_function(env, listener_callback_object,
                                                 nullptr, res_name,
                                                 0, 2,
                                                 nullptr, nullptr, nullptr,
                                                 notification_cb,
                                                 &listener_callback);
        if (status != napi_ok) return nullptr;
        if (listener_type_str == "press") {
            keyboard_listener->add_event_listener(event_type::KEY_DOWN,
                                                  [listener_callback]
                                                  (KeyboardEvent* event) {
                napi_acquire_threadsafe_function(listener_callback);
                napi_call_threadsafe_function(listener_callback,
                                              reinterpret_cast<void*>(event),
                                              napi_tsfn_blocking);
            });
        } else if (listener_type_str == "release") {
            keyboard_listener->add_event_listener(event_type::KEY_UP,
                                                  [listener_callback]
                                                  (KeyboardEvent* event) {
                napi_acquire_threadsafe_function(listener_callback);
                napi_call_threadsafe_function(listener_callback,
                                              reinterpret_cast<void*>(event),
                                              napi_tsfn_blocking);
            });
        } else {
            // TODO(tommymchugh): Handle unknown listener type
        }
        return nullptr;
    }, SystemInstance::GetInstance(), &listener_key);
    if (status != napi_ok) return status;
    status = napi_set_named_property(env,
                                     keyboard,
                                     "addEventListener",
                                     listener_key);
    if (status != napi_ok) return status;

    // Declare and place keyboards apis binding within v11.keyboard
    status = napi_set_named_property(env, exports, "keyboard", keyboard);
    if (status != napi_ok) return status;
    return status;
}


// Initialize all variables and functions
void init(napi_env env, napi_value exports) {
    napi_status sound_status = sound(env, exports);
    if (sound_status != napi_ok) {
        napi_throw_error(env,
                         nullptr,
                         "Failed to initialize devices/sound");
        return;
    }

    napi_status keyboard_status = keyboard(env, exports);
    if (keyboard_status != napi_ok) {
        napi_throw_error(env,
                         nullptr,
                         "Failed to initialize devices/keyboard");
        return;
    }
}

}  // namespace devices
