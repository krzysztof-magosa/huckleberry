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

#ifndef __Huckleberry__Gpio__Pin__
#define __Huckleberry__Gpio__Pin__

#include <string>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include <poll.h>
#include "huckleberry/util/BiMap.hpp"

namespace huckleberry { namespace gpio {
    class Chip;

    class Pin {
    public:
        Pin(Chip& chip, const int no);
        ~Pin(void);

        enum Direction {
            In,
            Out
        };

        enum Value {
            Low,
            High
        };

        enum Edge {
            None,
            Rising,
            Falling,
            Both
        };

        void setDirection(Direction direction);
        Direction getDirection(void);
        void setValue(Value state);
        Value getValue(void);
        void setEdge(Edge edge);
        Edge getEdge(void);
        void onInterrupt(std::function<void (Pin*)> func);
        void setInterruptDebounce(uint64_t microseconds);
        void waitForInterrupt(void);
        
    protected:
        static const std::string GPIO_PATH;
        static const huckleberry::util::BiMap<Direction, std::string> DIRECTION_MAP;
        static const huckleberry::util::BiMap<Value, std::string> VALUE_MAP;
        static const huckleberry::util::BiMap<Edge, std::string> EDGE_MAP;

        std::vector<std::function<void (Pin*)> > interruptHandlers;
        std::thread* interruptThread;
        int number;
        Chip& chip;
        std::string path;
        std::fstream directionFile;
        std::fstream valueFile;
        std::fstream edgeFile;
        uint64_t interruptDebounce;
        uint64_t lastInterrupt;
        void doExport(void);
        void doUnexport(void);

        void startInterruptThread(void);
    };
} }

#endif
