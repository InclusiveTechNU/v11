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

// ! IGNORE-ERROR
// TODO(tommymchugh): Unknown module from native gyp binding
// eslint-disable-next-line @typescript-eslint/ban-ts-ignore
// @ts-ignore
// eslint-disable-next-line node/no-unpublished-import
import * as larkin from '../../../larkin/Release/larkin';
// ! END-IGNORE-ERROR

import * as Types from 'larkin-types';
export type SpeechAPI = Types.SpeechAPI;
export type PlatformAPI = Types.PlatformAPI;
export type UtilsAPI = Types.UtilsAPI;
export type KeyboardAPI = Types.KeyboardAPI;
export type NotificationsAPI = Types.NotificationsAPI;
export type ApplicationAPI = Types.ApplicationAPI;
export type AccessibilityAPI = Types.AccessibilityAPI;

export type Window = Types.Window;
export type Application = Types.Application;
export type Event = Types.Event;
export type Voice = Types.Voice;
export type Version = Types.Version;

export const speech: SpeechAPI = larkin.speech;
export const platform: PlatformAPI = larkin.platform;
export const utils: UtilsAPI = larkin.utils;
export const keyboard: KeyboardAPI = larkin.keyboard;
export const notifications: NotificationsAPI = larkin.notifications;
export const applications: ApplicationAPI = larkin.applications;
export const accessibility: AccessibilityAPI = larkin.accessibility;
