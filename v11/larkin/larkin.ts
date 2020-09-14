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

// TODO(tommymchugh): Unknown module error from native gyp binding
// eslint-disable-next-line @typescript-eslint/ban-ts-ignore
// @ts-ignore
import * as larkinAddon from './runtime/node/larkin_node_addon.js';

// Export all addon modules from the native bindings
export const speech: SpeechAPI = larkinAddon.speech;
export const platform: PlatformAPI = larkinAddon.platform;
export const utils: UtilsAPI = larkinAddon.utils;
export const keyboard: KeyboardAPI = larkinAddon.keyboard;
export const notifications: NotificationsAPI = larkinAddon.notifications;
export const applications: ApplicationAPI = larkinAddon.applications;
export const accessibility: AccessibilityAPI = larkinAddon.accessibility;
