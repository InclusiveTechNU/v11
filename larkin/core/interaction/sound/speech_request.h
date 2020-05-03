/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <string>
#include "interaction/sound/text2speech/voice.h"

namespace sound {
namespace voice {

typedef pid_t request_id;

struct speech_request {
    request_id id;
    const Voice* voice;
    std::string text;
};

};  // namespace voice
};  // namespace sound
