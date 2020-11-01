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
import * as addon from './node/core_node_addon.js';

// Export all types through core as a new type module
import type * as Types from 'core';
export {Types};

// Declare public facing core API types
export const speech: Types.SpeechAPI = addon.speech;
export const platform: Types.PlatformAPI = addon.platform;
export const utils: Types.UtilsAPI = addon.utils;
export const keyboard: Types.KeyboardAPI = addon.keyboard;
export const notifications: Types.NotificationsAPI = addon.notifications;
export const applications: Types.ApplicationAPI = addon.applications;
export const accessibility: Types.AccessibilityAPI = addon.accessibility;
