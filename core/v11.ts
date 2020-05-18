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

import * as larkin from '../larkin/client/larkin';

// * v11.speech
// v11.speech is a replica of the larkin speech synthesis API. The
// implementation of the API is just an export of the larkin component
interface SpeechAPI extends larkin.SpeechAPI {
  getVoiceByName(name: string): Array<larkin.Voice>;
  getVoiceById(id: string): Array<larkin.Voice>;
  filterVoices(filter: (voice: larkin.Voice) => boolean): Array<larkin.Voice>;
}

export const speech: SpeechAPI = {
  getVoices: larkin.speech.getVoices,
  getDefaultVoice: larkin.speech.getDefaultVoice,

  filterVoices: (filter: (voice: larkin.Voice) => boolean) => {
    return speech.getVoices().filter((voice: larkin.Voice) => {
      return filter(voice);
    });
  },
  getVoiceByName: (name: string) => {
    return speech.filterVoices((voice: larkin.Voice) => {
      if (voice.name === name) return true;
      return false;
    });
  },
  getVoiceById: (id: string) => {
    return speech.filterVoices((voice: larkin.Voice) => {
      if (voice.id === id) return true;
      return false;
    });
  },
};
