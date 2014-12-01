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

#ifndef __Huckleberry__Util__BiMap__
#define __Huckleberry__Util__BiMap__

#include <map>

/**
 * Very primitive bi-directional map based on two normal std::map.
 */
namespace huckleberry { namespace util {

    template<typename firstT, typename secondT>
    class BiMap {
    public:
        BiMap(std::map<firstT, secondT> map)
        {
            typename std::map<firstT, secondT>::iterator iter;

            for (iter = map.begin(); iter != map.end(); iter++) {
                normal[iter->first] = iter->second;
                reverse[iter->second] = iter->first;
            }
        }

        secondT toValue(firstT key) const
        {
            return normal.at(key);
        }

        firstT fromValue(secondT value) const
        {
            return reverse.at(value);
        }

    protected:
        std::map<firstT, secondT> normal;
        std::map<secondT, firstT> reverse;
    };

} }

#endif
