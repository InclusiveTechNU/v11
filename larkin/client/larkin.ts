/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// ! IGNORE-ERROR: Unknown module from native gyp binding
import * as larkin from '../../../bazel-bin/larkin/client/node/build/Release/larkin.node';
import * as Types from 'larkin-types';

export const speech: Types.SpeechAPI = larkin.speech;
export type SpeechAPI = Types.SpeechAPI;
