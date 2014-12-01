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

#include "huckleberry/gpio/Chip.hpp"
#include <fstream>

namespace huckleberry { namespace gpio {

    Chip::Chip(const int number): number(number)
    {
        std::string tmp;

        std::ifstream baseFile("/sys/class/gpio/gpiochip"+std::to_string(number)+"/base");
        if (!baseFile.is_open()) {
            throw new std::invalid_argument("Specified gpio chip doesn't exist.");
        }
        std::getline(baseFile, tmp);
        baseFile.close();
        base = std::stoi(tmp);
        
        std::ifstream ngpioFile("/sys/class/gpio/gpiochip"+std::to_string(number)+"/ngpio");
        std::getline(ngpioFile, tmp);
        ngpioFile.close();
        ngpio = std::stoi(tmp);

        pinsRange = std::make_pair(base, base+ngpio-1);
    }

    Pin& Chip::getPin(const int number)
    {
        const int alignedNumber = base + number;
        auto search = pins.find(alignedNumber);

        if (search != pins.end()) {
            return *search->second;
        }
        else {
            if (alignedNumber < pinsRange.first || alignedNumber > pinsRange.second) {
                throw new std::out_of_range("Pin number is outside range controlled by this chip.");
            }

            pins[alignedNumber] = new Pin(*this, alignedNumber);
            return *pins[alignedNumber];
        }
    }

} }
