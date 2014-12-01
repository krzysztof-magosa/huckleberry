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

#include "huckleberry/spi/driver/Mcp3008.hpp"

namespace huckleberry { namespace spi { namespace driver {

    Mcp3008::Mcp3008(huckleberry::spi::Device& device): device(device)
    {
    }

    uint16_t Mcp3008::getValue(int channel)
    {
        channel--;

        if (channel < 0 || channel > 7) {
            throw new std::out_of_range("Channel number must be between 1 and 8.");
        }

        auto response = device.transfer(
            {
                1,
                (uint8_t)((8 + channel) << 4),
                0
            }
        );

        return (((response->at(1) & 3) << 8) + response->at(2));
    }

    double Mcp3008::getPercentage(int channel)
    {
        return getValue(channel) / max;
    }

} } }
