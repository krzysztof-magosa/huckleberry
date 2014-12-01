add_library (
    huckleberry SHARED
    util/Time.cpp
)

target_link_libraries (huckleberry pthread)
