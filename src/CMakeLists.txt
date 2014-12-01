add_library (
    huckleberry SHARED
    util/Time.cpp
    spi/Bus.cpp
    spi/Device.cpp
)

target_link_libraries (huckleberry pthread)
