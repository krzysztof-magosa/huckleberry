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

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "huckleberry/gpio/Pin.hpp"
#include "huckleberry/util/Time.hpp"

namespace huckleberry { namespace gpio {

    const std::string Pin::GPIO_PATH = "/sys/class/gpio";

    const huckleberry::util::BiMap<Pin::Direction, std::string> Pin::DIRECTION_MAP(
        {
            {Pin::Direction::In,    "in"},
            {Pin::Direction::Out,   "out"}
        }
    );

    const huckleberry::util::BiMap<Pin::Value, std::string> Pin::VALUE_MAP(
        {
            {Pin::Value::Low,       "0"},
            {Pin::Value::High,      "1"}
        }
    );

    const huckleberry::util::BiMap<Pin::Edge, std::string> Pin::EDGE_MAP(
        {
            {Pin::Edge::None,       "none"},
            {Pin::Edge::Rising,     "rising"},
            {Pin::Edge::Falling,    "falling"},
            {Pin::Edge::Both,       "both"}
        }
    );

    Pin::Pin(Chip& chip, const int number): chip(chip), number(number)
    {
        path = GPIO_PATH + "/gpio" + std::to_string(number);

        doExport();
        
        directionFile = new std::fstream();
        valueFile = new std::fstream();
        edgeFile = new std::fstream();

        directionFile->open(path + "/direction");
        valueFile->open(path + "/value");
        edgeFile->open(path + "/edge");

        lastInterrupt = 0;
        interruptDebounce = 0;

        startInterruptThread();
    }

    Pin::~Pin(void)
    {
        doUnexport();
    }

    void Pin::setDirection(Direction direction)
    {
        *directionFile << DIRECTION_MAP.toValue(direction) << std::endl;
    }

    Pin::Direction Pin::getDirection(void)
    {
        std::string value;
        getline(*directionFile, value);

        return DIRECTION_MAP.fromValue(value);        
    }

    void Pin::setValue(Pin::Value value)
    {
        *valueFile << VALUE_MAP.toValue(value) << std::endl;
    }

    Pin::Value Pin::getValue(void)
    {
        std::string line;
        valueFile->seekg(std::ios_base::beg);
        getline(*valueFile, line);

        return VALUE_MAP.fromValue(line);
    }

    void Pin::setEdge(Pin::Edge edge)
    {
        *edgeFile << EDGE_MAP.toValue(edge) << std::endl;
    }

    Pin::Edge Pin::getEdge(void)
    {
        std::string line;
        valueFile->seekg(std::ios_base::beg);
        getline(*edgeFile, line);

        return EDGE_MAP.fromValue(line);
    }

    void Pin::setInterruptDebounce(uint64_t microseconds)
    {
        this->interruptDebounce = microseconds;
    }

    void Pin::startInterruptThread(void)
    {
        interruptThread = new std::thread(
            [this] () {
                const char *name = (path + "/value").c_str();
                struct pollfd fdset[1];
                char buf[1000];

                memset((void*)fdset, 0, sizeof(fdset));
                fdset[0].fd = open(name, O_RDONLY | O_NONBLOCK);
                fdset[0].events = POLLPRI;

                read(fdset[0].fd, buf, 1000);

                while (true) {
                    if (poll(fdset, 1, 0)) {
                        if (fdset[0].revents & POLLPRI) {
                            lseek(fdset[0].fd, 0, SEEK_SET);
                            read(fdset[0].fd, buf, 1000);

                            long now = huckleberry::util::Time::microtime();

                            if (now - lastInterrupt >= interruptDebounce) {
                                for (auto func : interruptHandlers) {
                                    func(this);
                                }

                                lastInterrupt = now;
                            }
                        }
                    }
                }
            }
        );
    }

    void Pin::onInterrupt(std::function<void (Pin*)> func)
    {
        interruptHandlers.push_back(func);
    }

    void Pin::waitForInterrupt(void)
    {
        const char *name = (path + "/value").c_str();
        struct pollfd fdset[1];
        char buf[1000];

        memset((void*)fdset, 0, sizeof(fdset));
        fdset[0].fd = open(name, O_RDONLY | O_NONBLOCK);
        fdset[0].events = POLLPRI;

        read(fdset[0].fd, buf, 1000);

        while (true) {
            if (poll(fdset, 1, 0)) {
                if (fdset[0].revents & POLLPRI) {
                    lseek(fdset[0].fd, 0, SEEK_SET);
                    read(fdset[0].fd, buf, 1000);

                    break;
                }
            }
        }
    }

    void Pin::doExport(void)
    {
        std::ofstream file;
        file.open(GPIO_PATH + "/export");
        file << std::to_string(number) << std::endl;
    }

    void Pin::doUnexport(void)
    {
        std::ofstream file;
        file.open(GPIO_PATH + "/unexport");
        file << std::to_string(number) << std::endl;
    }
    
} }
