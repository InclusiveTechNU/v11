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

// larkin.d.ts
// Provides the typescript declarations for the larkin native bindings
declare module 'larkin' {
  interface Voice {
    id: string;
    name: string;
    gender: string;
    age: number;
    locale: string;
  }

  interface Version {
    major: number;
    minor: number;
    patch: number;
  }

  interface Event {
    id: string;
    name: string;
  }

  interface KeyboardEvent {
    type: string;
    key: number;
  }

  interface NotificationsAPI {
    addEventListener(type: string, callback: (event?: Event) => void): void;
  }

  interface Application {
    id: string;
    name: string;
    processId: string;
  }

  interface ApplicationAPI {
    activate(processId: number): void;
    getApplications(): Array<Application>;
  }

  interface Window {
    title: string;
    native: {};
  }

  interface Element {
    type: string;
    title?: string;
    value?: string;
    label?: string;
    native: {};
  }

  interface AccessibilityAPI {
    getWindows(pid: number): Array<Window>;
    setValue(native: {}, text: string): void;
    performAction(native: {}, name: string): void;
    getActions(native: {}): Array<string>;
    getChildren(native: {}): Array<Element>;
    addEventListener(native: {},
                      type:string,
                      callback: () => void): void;
  }

  interface PlatformAPI {
    type: string;
    version: Version;
  }

  interface UtilsAPI {
    run(): void;
  }

  interface KeyboardSimulationAPI {
    holdKey(): void;
    releaseKey(): void;
  }

  interface KeyboardAPI {
    simulation: KeyboardSimulationAPI;
    addEventListener(type: string, callback: (event?: KeyboardEvent) => void): void;
  }

  interface SpeechAPI {
    getVoices(): Array<Voice>;
    getDefaultVoice(): Voice;
    speak(text: string, voiceId: string, callback?: () => void): void;
  }
}
