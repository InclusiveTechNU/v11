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

#pragma once

#include "core/devices/device_base.h"

namespace devices {

template <typename Listener, typename Dispatcher>
DeviceBase<Listener, Dispatcher>::~DeviceBase() {
    delete listener_;
    delete dispatcher_;
}

template <typename Listener, typename Dispatcher>
DeviceType DeviceBase<Listener, Dispatcher>::GetType() const {
    return type_;
}

template <typename Listener, typename Dispatcher>
Listener* const DeviceBase<Listener, Dispatcher>::GetListener() const {
    return listener_;
}

template <typename Listener, typename Dispatcher>
Dispatcher* const DeviceBase<Listener, Dispatcher>::GetDispatcher() const {
    return dispatcher_;
}

}  // namepsace devices
