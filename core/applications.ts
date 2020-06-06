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
  title?: string;
  value?: string;
  label?: string;

  constructor(element: larkin.Element) {
    this.type = processType(element.type);
    this.title = element.title;
    this.value = element.value;
    this.label = element.label;
    this._native = element.native;
  }

  get children(): Array<Element> {
    return larkin.accessibility.getChildren(this._native).map(child => {
      return new Element(child);
    });
  }

  getElementsByType(type: string): Array<Element> {
    let elements: Array<Element> = [];
    const checkEachChild = (children: Array<Element>) => {
      elements = elements.concat(
        children.filter(element => {
          return element.type === type;
        })
      );
      if (children.length > 0) {
        children.forEach(child => checkEachChild(child.children));
      }
    };
    this.children.forEach(child => checkEachChild(child.children));
    return elements;
  }

  getElementsByLabel(label: string): Array<Element> {
    let elements: Array<Element> = [];
    const checkEachChild = (children: Array<Element>) => {
      elements = elements.concat(
        children.filter(element => {
          return element.label ?? '' === label;
        })
      );
      if (children.length > 0) {
        children.forEach(child => checkEachChild(child.children));
      }
    };
    this.children.forEach(child => checkEachChild(child.children));
    return elements;
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

  getElementsByType(type: string): Array<Element> {
    let elements: Array<Element> = [];
    this.children.forEach(child => {
      elements = elements.concat(child.getElementsByType(type));
    });
    return elements;
  }

  getElementsByLabel(label: string): Array<Element> {
    let elements: Array<Element> = [];
    this.children.forEach(child => {
      elements = elements.concat(child.getElementsByLabel(label));
    });
    return elements;
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

  getElementsByType(type: string): Array<Element> {
    let elements: Array<Element> = [];
    this.windows.forEach(window => {
      elements = elements.concat(window.getElementsByType(type));
    });
    return elements;
  }

  getElementsByLabel(label: string): Array<Element> {
    let elements: Array<Element> = [];
    this.windows.forEach(window => {
      elements = elements.concat(window.getElementsByLabel(label));
    });
    return elements;
  }
}
