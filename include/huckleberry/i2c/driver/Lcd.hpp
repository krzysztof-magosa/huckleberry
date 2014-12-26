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

#ifndef __Huckleberry__I2c__Driver__Lcd__
#define __Huckleberry__I2c__Driver__Lcd__

#include <cstdint>
#include <stdexcept>
#include "huckleberry/i2c/Device.hpp"

namespace huckleberry { namespace i2c { namespace driver {

    class Lcd
    {
    public:
        Lcd(huckleberry::i2c::Device& device);
        void init(void);
        void strobe(void);
        void write(uint8_t value);
        void clear(void);
        void writeChar(char letter);
        void writeText(std::string text);
        void jumpToLine(int const line);
        void setBacklight(bool const enabled);
        void setDisplay(bool const enabled);
        void setCursor(bool const enabled);
        void setBlink(bool const enabled);

    protected:
        void setDisplayControlFlag(uint8_t const flag, bool const enabled);
        void sendDisplayControl(void);

        class Cmd
        {
        public:
            static uint8_t const clearDisplay       = 0x01;
            static uint8_t const returnHome         = 0x02;
            static uint8_t const entryModeSet       = 0x04;
            static uint8_t const displayControl     = 0x08;
            static uint8_t const cursorShift        = 0x10;
            static uint8_t const functionSet        = 0x20;
            static uint8_t const setCgRamAddress    = 0x40;
            static uint8_t const setDdRamAddress    = 0x80;
        };

        class Flag
        {
        public:
            static uint8_t const bitMode8           = 0x10;
            static uint8_t const bitMode4           = 0x00;
            static uint8_t const line2              = 0x08;
            static uint8_t const line1              = 0x00;
            static uint8_t const dots5x10           = 0x04;
            static uint8_t const dots5x8            = 0x00;
            static uint8_t const displayOn          = 0x04;
            static uint8_t const displayOff         = 0x00;
            static uint8_t const cursorOn           = 0x02;
            static uint8_t const cursorOff          = 0x00;
            static uint8_t const blinkOn            = 0x01;
            static uint8_t const blinkOff           = 0x00;
            static uint8_t const entryRight         = 0x00;
            static uint8_t const entryLeft          = 0x02;
            static uint8_t const entryShiftInc      = 0x01;
            static uint8_t const entryShiftDec      = 0x00;
            static uint8_t const displayMove        = 0x08;
            static uint8_t const cursorMove         = 0x00;
            static uint8_t const moveRight          = 0x04;
            static uint8_t const moveLeft           = 0x00;
            static uint8_t const registerData       = 0x01;
        };

        class Bit
        {
        public:
            static uint8_t const enable            = 0b00000100; // instruct lcd to read data
            static uint8_t const readWrite         = 0b00000010; // read if used, write otherwise
            static uint8_t const registerSelect    = 0b00000001; // data if used, instruction otherwise

            static uint8_t const backlightEnabled  = 0b00001000;
            static uint8_t const backlightDisabled = 0b00000000;

            static uint8_t const clearDisplay      = 0b00000001;
            static uint8_t const cursorHome        = 0b00000010;
            static uint8_t const write             = 0b10000000;
            static uint8_t const setCgRamAddress   = 0b01000000;
            // static uint8_t const setDdRamAddress   = 0b10000000;
            // static uint8_t const setDdRamAddress   = 0b00101000;
            static uint8_t const setDdRamAddress = 0x80;
        };

        huckleberry::i2c::Device& device;
        int columns;
        int lines;

        uint8_t backlightBit;
        uint8_t displayControl;
        uint8_t displayMode;
        uint8_t displayShift;
    };

} } }

#endif
