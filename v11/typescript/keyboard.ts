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

import * as core from '../core/core';

export enum KeyboardAction {
  press = 'press',
  release = 'release'
}

export type KeyboardEvent = core.Types.KeyboardEvent;

// * v11.keyboard
// v11.keyboard provides resources and methods for simulating and listening
// for system keyboard events
interface KeyboardAPI {
  pressKey(key: number): void;
  pressKeys(keys: Array<number>): void;
  holdKey(key: number): void;
  releaseKey(key: number): void;
  sendKeyEvent(key: number, action: KeyboardAction): void;
  addEventListener(type: KeyboardAction, callback: (event: KeyboardEvent) => void): void;
}

// Public Speech API
export const keyboard: KeyboardAPI = {
  pressKey: (key: number) => {
    keyboard.holdKey(key);
    keyboard.releaseKey(key);    
  },
  pressKeys: (keys: Array<number>) => {
    keys.forEach((key) => {
      keyboard.pressKey(key);
    });
  },
  holdKey: (key: number) => {
    keyboard.sendKeyEvent(key, KeyboardAction.press);
  },
  releaseKey: (key: number) => {
    keyboard.sendKeyEvent(key, KeyboardAction.release);
  },
  sendKeyEvent: (key: number, action: KeyboardAction) => {
    if (action === KeyboardAction.press) {
      core.keyboard.simulation.holdKey(key);
    } else if (action === KeyboardAction.release) {
      core.keyboard.simulation.releaseKey(key);
    } else {
      // TODO(tommymchugh): Manage error failure
    }
  },
  addEventListener: (type: KeyboardAction, callback: (event: KeyboardEvent) => void) => {
    core.keyboard.addEventListener(type.toString(), (e: KeyboardEvent | undefined) => {
      callback(e!);
    });
  }
};
