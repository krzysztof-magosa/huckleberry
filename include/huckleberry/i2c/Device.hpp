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

#ifndef __Huckleberry__I2c__Device__
#define __Huckleberry__I2c__Device__

#include <cstdint>
#include <vector>

namespace huckleberry { namespace i2c {
    class Chip;
    class SmBus;

    class Device
    {
    friend SmBus;

    public:
        Device(Chip& chip, const int address);
        SmBus& smBus(void);

    protected:
        Chip& chip;
        SmBus* smBusInstance;
        int address;
        int fd;
    };

} }

#endif
