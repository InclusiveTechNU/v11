/*
 * Copyright (c) Northwestern Inclusive Technology Lab
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @flow
const larkin = require("../../bazel-bin/larkin/client/node/build/Release/larkin");

// * Speech Synthesis API
// * v11.speech
// v11.speech is a replica of the larkin speech synthesis API. The
// implementation of the API is just an export of the larkin component
exports.speech = larkin.speech;
