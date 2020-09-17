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

#include "larkin/runtime/node/sound_utils.h"

namespace interaction {
namespace utils {
namespace sound {

napi_status voice_to_object(napi_env env,
                            const Voice* voice,
                            napi_value object) {
    napi_status s;
    // Object item id set to string voice get_id
    napi_value voice_id;
    s = napi_create_string_utf8(env,
                                voice->get_id(),
                                NAPI_AUTO_LENGTH,
                                &voice_id);
    if (s != napi_ok) return s;
    s = napi_set_named_property(env, object, "id", voice_id);
    if (s != napi_ok) return s;

    // Object item name set to string voice get_name
    napi_value voice_name;
    s = napi_create_string_utf8(env,
                                voice->get_name(),
                                NAPI_AUTO_LENGTH,
                                &voice_name);
    if (s != napi_ok) return s;
    s = napi_set_named_property(env, object, "name", voice_name);
    if (s != napi_ok) return s;

    // Object item gender set to string voice get_gender
    napi_value voice_gender;
    s = napi_create_string_utf8(env,
                                voice->get_gender(),
                                NAPI_AUTO_LENGTH,
                                &voice_gender);
    if (s != napi_ok) return s;
    s = napi_set_named_property(env, object, "gender", voice_gender);
    if (s != napi_ok) return s;

    // Object item age set to string voice get_age
    napi_value voice_age;
    s = napi_create_int32(env,
                          voice->get_age(),
                          &voice_age);
    if (s != napi_ok) return s;
    s = napi_set_named_property(env, object, "age", voice_age);
    if (s != napi_ok) return s;

    // Object item locale set to string voice get_locale
    napi_value voice_locale;
    s = napi_create_string_utf8(env,
                                voice->get_locale(),
                                NAPI_AUTO_LENGTH,
                                &voice_locale);
    if (s != napi_ok) return s;
    s = napi_set_named_property(env, object, "locale", voice_locale);
    if (s != napi_ok) return s;

    // Object item age set to string voice age
    /*napi_value voice_age;
    s = napi_create_string_utf8(env,
                                voice->get_age(),
                                NAPI_AUTO_LENGTH,
                                &voice_age);
    if (s != napi_ok) return s;
    s = napi_set_named_property(env, object, "age", voice_age);
    if (s != napi_ok) return s;*/
    return s;
}

}  // namespace sound
}  // namespace utils
}  // namespace interaction
