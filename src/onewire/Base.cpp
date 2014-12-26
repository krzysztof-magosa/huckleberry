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

#include "huckleberry/onewire/Base.hpp"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

namespace huckleberry { namespace onewire {

    Base::Base(uint64_t const serial): serial(serial)
    {
        std::ifstream name(getPath() + "/name");
        if (!name.is_open()) {
            throw new std::runtime_error("Cannot open device.");
        }
    }

    std::string Base::getPath(void)
    {
        uint8_t classId = serial & 0xff;
        uint64_t deviceId = (serial >> 8);

        std::stringstream path;
        path << "/sys/bus/w1/devices/";
        path << std::hex;
        path << std::setfill('0') << std::setw(2) << (int)classId;
        path << "-";
        path << std::setfill('0') << std::setw(12) << deviceId;

        return path.str();
    }

} }
