/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// larkin.d.ts
// Provides the typescript declarations for the larkin native bindings

declare module 'larkin-types' {
  interface SpeechAPI {
    getVoices(): Array<any>;
  }
}
