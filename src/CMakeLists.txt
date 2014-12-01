add_library (
    huckleberry SHARED
    util/Time.cpp
    spi/Bus.cpp
    spi/Device.cpp
    spi/driver/Mcp3008.cpp
    gpio/Pin.cpp
    gpio/Chip.cpp
)

target_link_libraries (huckleberry pthread)
