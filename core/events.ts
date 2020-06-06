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

export type Event = larkin.Event;

// * EventTarget
// @type: interface
// Event Target objects are able to receive and be notified of events
// that occur specifically to the object. The main event targets
// are Applications and the System. System can be notified of all
// events while Applications can be notified of only relevant events.
export interface EventTarget extends larkin.NotificationsAPI {
  onlaunch?: (event?: Event) => void;
  onhide?: (event?: Event) => void;
  onunhide?: (event?: Event) => void;
  onterminate?: (event?: Event) => void;
}
