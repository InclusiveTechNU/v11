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

// * v11.system
// v11.system implements objects and methods related to observing
// the state of the platform that the V11 runtime is being on top off.
// Includes v11.system.platform: an object of specific platform info
const PLATFORM_APPLE = 'apple';
const PLATFORM_WINDOWS = 'windows';
const PLATFORM_LINUX = 'linux';
const PLATFORM_UNKNOWN = 'unknown';

interface Platform {
  type: string;
}

interface SystemAPI {
  platform: Platform;
  isApple: boolean;
  isWindows: boolean;
  isLinux: boolean;
}

const systemPlatform: Platform = {
  type: larkin.platform.type,
};

const isPlatform = (platform: string) => {
  return systemPlatform.type === platform;
};

export const system: SystemAPI = {
  platform: systemPlatform,
  isApple: isPlatform(PLATFORM_APPLE),
  isWindows: isPlatform(PLATFORM_WINDOWS),
  isLinux: isPlatform(PLATFORM_LINUX),
};
