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

#include "huckleberry/i2c/SmBus.hpp"
#include "huckleberry/i2c/Device.hpp"
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

namespace huckleberry { namespace i2c {

    SmBus::SmBus(Device& device) : device(device)
    {
    }

    void SmBus::writeByte(uint8_t value)
    {
        if (i2c_smbus_write_byte(device.fd, value) == -1) {
            // 
        }
    }

    void SmBus::writeBytes(std::vector<uint8_t> values)
    {
        for (uint8_t value : values) {
            writeByte(value);
        }
    }

    void SmBus::writeByteData(uint8_t command, uint8_t value)
    {
        if (i2c_smbus_write_byte_data(device.fd, command, value) < 0) {
            //
        }
    }

    uint8_t SmBus::readByte(void)
    {
        // 
        return i2c_smbus_read_byte(device.fd);
    }



} }
