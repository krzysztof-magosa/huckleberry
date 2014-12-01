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

#include <cstdio>
#include <sys/time.h>
#include "huckleberry/util/Time.hpp"

namespace huckleberry { namespace util {

    uint64_t Time::microtime(void)
    {
        timeval time;
        gettimeofday(&time, NULL);
        return ((uint64_t)time.tv_sec * 1000000) + time.tv_usec;
    }

    /**
     * To be used in situations when normal sleep functions cannot
     * handle so small times.
     */
    uint64_t Time::microsleep(const uint64_t microsends)
    {
        const uint64_t finish = microtime() + microsends;
        uint64_t current;

        do {
            current = microtime();
        } while (current <= finish);

        return finish - current;
    }

} }
