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

v11.system.onlaunch = (event) => {
    console.log(event);
}

/*v11.system.addEventListener('launch', (app) => {
    console.log(app);
    v11.speech.speak(`${app.name} launched!`, v11.speech.getVoiceByName("Ting-Ting")[0]);
});

v11.system.addEventListener('hide', (app) => {
    console.log(app);
    v11.speech.speak(`${app.name} hid!`, v11.speech.getVoiceByName("Ting-Ting")[0]);
});

v11.system.addEventListener('terminate', (app) => {
    console.log(app);
    v11.speech.speak(`${app.name} quit!`, v11.speech.getVoiceByName("Ting-Ting")[0]);
});*/

v11.start();