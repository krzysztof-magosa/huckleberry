/**
 * Copyright 2014 Krzysztof Magosa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "huckleberry/i2c/Chip.hpp"

namespace huckleberry { namespace i2c {

    Chip::Chip(const int number): number(number)
    {
    }

    Device Chip::getDevice(const int address)
    {
        auto search = devices.find(address);

        if (search != devices.end()) {
            return *search->second;
        }
        else {
            devices[address] = new Device(*this, address);
            return *devices[address];
        }
    }

    int Chip::getNumber(void)
    {
        return this->number;
    }

} }
