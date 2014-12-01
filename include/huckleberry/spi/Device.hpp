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

#ifndef __Huckleberry__Spi__Device__
#define __Huckleberry__Spi__Device__

#include <cstdint>
#include <vector>

namespace huckleberry { namespace spi {
    class Bus;

    class Device
    {
    public:
        Device(Bus& bus, const int number);

        std::vector<uint8_t>* transfer(std::vector<uint8_t> data);
        uint32_t getMaxSpeed(void);
        void setMaxSpeed(uint32_t speed);
        uint8_t getBitsPerWord(void);
        void setBitsPerWord(uint8_t bpw);
        uint8_t getMode(void);
        void setMode(uint8_t mode);

    protected:
        Bus& bus;
        int number;
        int fd;
    };

} }

#endif
