/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace sound {
namespace voice {

// TODO(tommymchugh): support enhanced and downloaded system voices
// See AVSpeechSynthesisVoiceQualityEnhanced at:
// developer.apple.com/documentation/avfoundation/avspeechsynthesisvoicequality

// Different levels of voice quality
// supported by the native system
enum voice_quality {
    DEFAULT
};

};  // namespace voice
};  // namespace sound
