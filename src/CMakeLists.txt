add_library (
    huckleberry SHARED
    util/Time.cpp
    spi/Bus.cpp
    spi/Device.cpp
    gpio/Pin.cpp
    gpio/Chip.cpp
)

target_link_libraries (huckleberry pthread)
