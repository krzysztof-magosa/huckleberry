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

#ifndef __Huckleberry__I2c__Chip__
#define __Huckleberry__I2c__Chip__

#include <cstdint>
#include <map>
#include "huckleberry/i2c/Device.hpp"

namespace huckleberry { namespace i2c {

    class Chip
    {
    public:
        Chip(const int number);
        Device getDevice(const int address);
        int getNumber(void);

    protected:
        int number;
        std::map<int, Device*> devices;
    };

} }

#endif
