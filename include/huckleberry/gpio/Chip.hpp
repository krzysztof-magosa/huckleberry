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

#ifndef __Huckleberry__Gpio__Chip__
#define __Huckleberry__Gpio__Chip__

#include "huckleberry/gpio/Pin.hpp"
#include <utility>

namespace huckleberry { namespace gpio {

    class Chip {
    public:
        Chip(const int number);
        Pin& getPin(const int number);

    protected:
        std::map<int, Pin*> pins;
        int number;
        int base;
        int ngpio;
        std::pair<int, int> pinsRange;
    };

} }

#endif
