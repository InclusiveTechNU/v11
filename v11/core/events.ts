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

import * as larkin from '../larkin/larkin';

export type Event = larkin.Event;

// * EventTarget
// @type: class
// Event Target objects are able to receive and be notified of events
// that occur specifically to the object. The main event targets
// are Applications and the System. System can be notified of all
// events while Applications can be notified of only relevant events.

export class EventTarget implements larkin.NotificationsAPI {
  private _onlaunch?: () => void;
  private _onhide?: () => void;
  private _onunhide?: () => void;
  private _onterminate?: () => void;
  public addEventListener: (
    type: string,
    callback: (event?: Event) => void
  ) => void;

  constructor(
    listenerMethod: (
      type: string,
      callback: (event?: Event | undefined) => void
    ) => void
  ) {
    this.addEventListener = listenerMethod;
  }

  get onlaunch(): ((event?: Event) => void) | undefined {
    return this._onlaunch;
  }
  set onlaunch(callback: ((event?: Event) => void) | undefined) {
    this._onlaunch = callback;
    if (callback !== undefined) {
      this.addEventListener('launch', callback);
    }
  }

  get onhide(): ((event?: Event) => void) | undefined {
    return this._onhide;
  }
  set onhide(callback: ((event?: Event) => void) | undefined) {
    this._onhide = callback;
    if (callback !== undefined) {
      this.addEventListener('hide', callback);
    }
  }

  get onunhide(): ((event?: Event) => void) | undefined {
    return this._onunhide;
  }
  set onunhide(callback: ((event?: Event) => void) | undefined) {
    this._onunhide = callback;
    if (callback !== undefined) {
      this.addEventListener('unhide', callback);
    }
  }

  get onterminate(): ((event?: Event) => void) | undefined {
    return this._onterminate;
  }
  set onterminate(callback: ((event?: Event) => void) | undefined) {
    this._onterminate = callback;
    if (callback !== undefined) {
      this.addEventListener('terminate', callback);
    }
  }
}
