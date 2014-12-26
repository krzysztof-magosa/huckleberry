add_library (
    huckleberry SHARED
    util/Time.cpp
    spi/Bus.cpp
    spi/Device.cpp
    spi/driver/Mcp3008.cpp
    gpio/Pin.cpp
    gpio/Chip.cpp
    i2c/Chip.cpp
    i2c/Device.cpp
    i2c/SmBus.cpp
)

target_link_libraries (huckleberry pthread)
