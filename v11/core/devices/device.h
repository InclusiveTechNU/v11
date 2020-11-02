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

#include <string>

namespace devices {

enum DeviceType {
    kKeyboardDevice,
    kSoundOutputDevice,
    kUnknownDevice,
};

template <typename Listener, typename Dispatcher>
class Device {
 public:
    virtual ~Device();

    virtual DeviceType GetType() const = 0;

    virtual const std::string* GetIdentifier() const = 0;

    virtual Listener* const GetListener() const = 0;

    virtual Dispatcher* const GetDispatcher() const = 0;
};

}  // namepsace devices

#include "core/devices/device_inl.h"
