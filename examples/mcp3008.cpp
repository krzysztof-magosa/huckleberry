#include <iostream>
#include "huckleberry/spi/Bus.hpp"
#include "huckleberry/spi/Device.hpp"
#include "huckleberry/spi/driver/Mcp3008.hpp"

namespace spi = huckleberry::spi;

int main(int argc, char** argv)
{
    spi::Bus bus(0);
    auto dev = bus.getDevice(0);
    spi::driver::Mcp3008 adc(dev);

    for (int i = 1; i <= 8; i++) {
        std::cout << "Channel " << i << ": " << adc.getValue(i) << std::endl;
    }

    return 0;
}
