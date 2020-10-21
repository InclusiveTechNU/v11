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

import * as larkin from '../larkin/larkin';

// * v11.speech
// v11.speech is a replica of the larkin speech synthesis API. The
// implementation of the API is just an export of the larkin component
interface PrivateSpeechAPI {
  speak(text: string, voiceId?: string, callback?: () => void): void;
}

interface SpeechAPI {
  // Voice-related methods
  filterVoices(filter: (voice: larkin.Types.Voice) => boolean): Array<larkin.Types.Voice>;
  getDefaultVoice(): larkin.Types.Voice;
  getVoiceById(id: string): Array<larkin.Types.Voice>;
  getVoiceByLocale(name: string): Array<larkin.Types.Voice>;
  getVoiceByName(name: string): Array<larkin.Types.Voice>;
  getVoices(): Array<larkin.Types.Voice>;

  // Speech Synthesis methods
  speak(text: string, voice?: larkin.Types.Voice): Promise<void>;
}

// Private Speech API
const _speech: PrivateSpeechAPI = {
  speak: (text: string, voiceId?: string, callback?: () => void) => {
    const guaranteedVoiceId = voiceId ?? speech.getDefaultVoice().id;
    larkin.speech.speak(text, guaranteedVoiceId, callback);
  },
};

// Public Speech API
export const speech: SpeechAPI = {
  getVoices: larkin.speech.getVoices,
  getDefaultVoice: larkin.speech.getDefaultVoice,

  filterVoices: (filter: (voice: larkin.Types.Voice) => boolean) => {
    return speech.getVoices().filter((voice: larkin.Types.Voice) => {
      return filter(voice);
    });
  },

  getVoiceByName: (name: string) => {
    return speech.filterVoices((voice: larkin.Types.Voice) => {
      return voice.name === name;
    });
  },

  getVoiceById: (id: string) => {
    return speech.filterVoices((voice: larkin.Types.Voice) => {
      return voice.id === id;
    });
  },

  getVoiceByLocale: (name: string) => {
    return speech.filterVoices((voice: larkin.Types.Voice) => {
      return voice.locale === name;
    });
  },

  speak: async (text: string, voice?: larkin.Types.Voice): Promise<void> => {
    return new Promise((resolve, _) => {
      _speech.speak(text, voice?.id ?? undefined, () => {
        resolve();
      });
    });
  },
};
