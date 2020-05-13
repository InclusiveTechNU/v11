/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "interaction/sound/text2speech/text2speech_synthesizer.h"

using sound::voice::Text2SpeechSynthesizer;
Text2SpeechSynthesizer synth = Text2SpeechSynthesizer();
synth.speak("Hello World!");
