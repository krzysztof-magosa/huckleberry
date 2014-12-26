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

#include "huckleberry/i2c/Chip.hpp"
#include "huckleberry/i2c/Device.hpp"
#include "huckleberry/i2c/SmBus.hpp"
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

namespace huckleberry { namespace i2c {

    Device::Device(Chip& chip, const int address) : chip(chip), address(address)
    {
        this->fd = open(
            ("/dev/i2c-" + std::to_string(this->chip.getNumber())).c_str(),
            O_RDWR
        );

        if (this->fd == -1) {
            throw new std::runtime_error("Error while opening I2C chip.");
        }

        if (ioctl(this->fd, I2C_SLAVE, address) == -1) {
            throw new std::runtime_error("Cannot select I2C device address.");
        }

        this->smBusInstance = new SmBus(*this);
    }

    SmBus& Device::smBus(void)
    {
        return *smBusInstance;
    }

} }
