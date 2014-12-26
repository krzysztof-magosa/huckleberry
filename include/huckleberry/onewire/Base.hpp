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

#ifndef __Huckleberry__Onewire__Base__
#define __Huckleberry__Onewire__Base__

#include <cstdint>
#include <string>
#include <sstream>

namespace huckleberry { namespace onewire {

    class Base
    {
    public:
        Base(uint64_t const serial);

    protected:
        std::string getPath(void);
        uint64_t const serial;
    };

} }

#endif
