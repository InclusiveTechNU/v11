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

interface ApplicationElement {
  type: string;
}

// TODO(tommymchugh): make this OS independent
const processType = (type: string): string => {
  return type.substring(2).toLowerCase();
};

export class Element implements ApplicationElement {
  private _native: {};
  type: string;

  constructor(element: larkin.Element) {
    this.type = processType(element.type);
    this._native = element.native;
  }

  get children(): Array<Element> {
    return larkin.accessibility.getChildren(this._native).map(child => {
      return new Element(child);
    });
  }
}

export class Window implements ApplicationElement {
  private _native: {};
  title: string;
  type: string;

  constructor(window: larkin.Window) {
    this.title = window.title;
    this.type = 'window';
    this._native = window.native;
  }

  get children(): Array<Element> {
    return larkin.accessibility.getChildren(this._native).map(child => {
      return new Element(child);
    });
  }
}

export class Application {
  private _pid: number;
  id: string;
  name: string;

  constructor(instance: larkin.Application) {
    this.id = instance.id;
    this.name = instance.name;
    this._pid = parseInt(instance.processId);
  }

  get windows(): Array<Window> {
    return larkin.accessibility.getWindows(this._pid).map(window => {
      return new Window(window);
    });
  }
}
