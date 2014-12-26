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

#include "huckleberry/i2c/driver/Lcd.hpp"
#include "huckleberry/i2c/SmBus.hpp"
#include "huckleberry/util/Time.hpp"

#include <bitset>
#include <iostream>

namespace huckleberry { namespace i2c { namespace driver {

    Lcd::Lcd(huckleberry::i2c::Device& device): device(device)
    {
        setBacklight(false);

        columns = 16;
        lines = 2;

        displayControl = Flag::displayOn | Flag::cursorOff | Flag::blinkOff;
        displayMode = Flag::entryLeft | Flag::entryShiftDec;
        displayShift = Flag::cursorMove | Flag::moveRight;
    }

    void Lcd::init(void)
    {
        // device.smBus().writeByte(0x20); // ???
        // strobe();
        // huckleberry::util::Time::microsleep(100); // time to be confirmed
        // write(Cmd::functionSet | Flag::bitMode4 | Flag::line2 | Flag::dots5x8);
        // write(Cmd::displayControl | displayControl);
        // write(Cmd::entryModeSet | displayMode);
        // write(Cmd::clearDisplay);
        // write(Cmd::cursorShift | displayShift);
        // write(Cmd::returnHome);
    }

    void Lcd::strobe(void)
    {
        uint8_t const en = 0b00000100;
        device.smBus().writeByte(device.smBus().readByte() | en | backlightBit);
        device.smBus().writeByte(device.smBus().readByte() | backlightBit & 0xfb);
    }

    void Lcd::write(uint8_t value)
    {
        device.smBus().writeByte((value & 0xf0) | backlightBit);
        device.smBus().readByte();
        strobe();

        device.smBus().writeByte((value << 4) | backlightBit);
        device.smBus().readByte();
        strobe();

        device.smBus().writeByte(backlightBit);
    }

    void Lcd::writeChar(char letter)
    {
        uint8_t control = backlightBit | Flag::registerData;

        device.smBus().writeByte(control | (letter & 0xf0));
        strobe();

        device.smBus().writeByte(control | (letter << 4));
        strobe();

        device.smBus().writeByte(backlightBit);

        huckleberry::util::Time::microsleep(37); // ???
    }

    void Lcd::writeText(std::string text)
    {
        for (char c : text) {
            writeChar(c);
        }
    }

    void Lcd::clear(void)
    {
        write(Bit::clearDisplay);
        // huckleberry::util::Time::microsleep(1.52*1000); // 1.52ms
        huckleberry::util::Time::microsleep(2*1000);
    }

    void Lcd::jumpToLine(int const line)
    {
        switch (line) {
            case 1:
                write(Bit::setDdRamAddress | 0x00);
                break;
            case 2:
                write(Bit::setDdRamAddress | 0x40);
                break;
        }
    }

    void Lcd::setBacklight(bool const enabled)
    {
        backlightBit = enabled ? Bit::backlightEnabled : Bit::backlightDisabled;
    }

    void Lcd::setDisplayControlFlag(uint8_t const flag, bool const enabled)
    {
        if (enabled) {
            displayControl |= flag;
        }
        else {
            displayControl &= ~flag;
        }

        sendDisplayControl();   
    }

    void Lcd::setDisplay(bool const enabled)
    {
        setDisplayControlFlag(Flag::displayOn, enabled);   
    }

    void Lcd::setCursor(bool const enabled)
    {
        setDisplayControlFlag(Flag::cursorOn, enabled);
    }

    void Lcd::setBlink(bool const enabled)
    {
        setDisplayControlFlag(Flag::blinkOn, enabled);
    }

    void Lcd::sendDisplayControl()
    {
        write(Cmd::displayControl | displayControl);
        huckleberry::util::Time::microsleep(37);
    }

} } }
