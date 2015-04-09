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

#include "huckleberry/spi/Bus.hpp"
#include "huckleberry/spi/Device.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <string>
#include <iostream>
#include <stdexcept>

namespace huckleberry { namespace spi {

    Device::Device(Bus& bus, const int number) : bus(bus), number(number)
    {
        this->fd = open(
            ("/dev/spidev" + std::to_string(this->bus.getNumber()) + "." + std::to_string(number)).c_str(),
            O_RDWR
        );

        if (this->fd == -1) {
            throw new std::runtime_error("Error while opening SPI device.");
        }
    }

    void Device::setMode(uint8_t mode)
    {
        if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {
            throw new std::runtime_error("Error while setting mode.");
        }
    }

    uint8_t Device::getMode(void)
    {
        uint8_t mode;
        if (ioctl(fd, SPI_IOC_RD_MODE, &mode) == -1) {
            throw new std::runtime_error("Error while getting mode.");
        }

        return mode;
    }

    uint32_t Device::getMaxSpeed(void)
    {
        uint32_t tmp = 0;
        if (ioctl(this->fd, SPI_IOC_RD_MAX_SPEED_HZ, &tmp) == -1) {
            throw new std::runtime_error("Error while getting max speed.");
        }
        return tmp;
    }

    void Device::setMaxSpeed(uint32_t speed)
    {
        if (ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
            throw new std::runtime_error("Error while setting max speed.");
        }
    }

    uint8_t Device::getBitsPerWord(void)
    {
        uint8_t tmp = 0;
        if (ioctl(this->fd, SPI_IOC_RD_BITS_PER_WORD, &tmp) == -1) {
            throw new std::runtime_error("Error while getting bits per word.");
        }
        return tmp;
    }

    void Device::setBitsPerWord(uint8_t bpw)
    {
        if (ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &bpw) == -1) {
            throw new std::runtime_error("Error while setting bits per word.");
        }
    }

    std::vector<uint8_t>* Device::transfer(std::vector<uint8_t> data)
    {
        struct spi_ioc_transfer xfer = {0};
        uint8_t* txBuf = (uint8_t*)malloc(data.size());
        uint8_t* rxBuf = (uint8_t*)malloc(data.size());

        for (int i = 0; i < data.size(); i++) {
            txBuf[i] = data[i];
        }

        xfer.tx_buf = (unsigned long)txBuf;
        xfer.rx_buf = (unsigned long)rxBuf;
        xfer.len = data.size();
        xfer.speed_hz = getMaxSpeed();
        xfer.bits_per_word = getBitsPerWord();

        if (ioctl(this->fd, SPI_IOC_MESSAGE(1), &xfer) == -1) {
            throw new std::runtime_error("Error while transferring data.");
        }

        auto response = new std::vector<uint8_t>();
        for (int i = 0; i < data.size(); i++) {
            response->push_back((uint8_t)rxBuf[i]);
        }

        free(txBuf);
        free(rxBuf);

        return response;
    }

} }
