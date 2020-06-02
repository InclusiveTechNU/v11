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

const v11 = require('../build/v11/core/v11');
var a = 1;

//v11.speech.speak("This is a test for the V11 platform.\
//                  This file's name is hello voice dot j s",
//                 v11.speech.getVoices()[7]);
v11.system.addEventListener('hide', () => {
    console.log("hello world");
});
