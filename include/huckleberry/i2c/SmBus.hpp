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

#ifndef __Huckleberry__I2c__SmBus__
#define __Huckleberry__I2c__SmBus__

#include <cstdint>
#include <vector>

namespace huckleberry { namespace i2c {
    class Device;

    class SmBus
    {
    public:
        SmBus(Device& device);
        void writeByte(uint8_t value);
        void writeBytes(std::vector<uint8_t> values);
        void writeByteData(uint8_t command, uint8_t value);
        uint8_t readByte(void);

    protected:
        Device& device;
    };

} }

#endif
