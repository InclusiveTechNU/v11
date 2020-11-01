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

#include "core/interaction/sound/text2speech/text2speech_delegate_mac.h"

@implementation Text2SpeechDelegate {
    SpeechDidFinishCallback* did_finish_callback;
}

- (id) init {
    self = [super init];
    did_finish_callback = nullptr;
    return self;
}

- (void)attachDidFinishCallback:(SpeechDidFinishCallback *)callback {
    did_finish_callback = callback;
}

- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender
        didFinishSpeaking:(BOOL)finishedSpeaking {
    if (did_finish_callback) {
        (*did_finish_callback)();
    }
}

@end