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
#include "core/devices/device.h"

namespace devices {

template <typename Listener, typename Dispatcher>
class DeviceBase : public Device<Listener, Dispatcher> {
 protected:
    DeviceType type_ = DeviceType::kUnknownDevice;
    Listener* listener_ = nullptr;
    Dispatcher* dispatcher_ = nullptr;

 public:
    virtual ~DeviceBase();

    // From Device Abstract Class definitions.
    DeviceType GetType() const;
    Listener* const GetListener() const;
    Dispatcher* const GetDispatcher() const;
    virtual const std::string* GetIdentifier() const = 0;
};

}  // namepsace devices

#include "core/devices/device_base_inl.h"
