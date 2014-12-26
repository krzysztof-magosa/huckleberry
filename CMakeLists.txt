cmake_minimum_required (VERSION 2.8.7)

project (Huckleberry)

if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif ()

include_directories (
    include
)

#enable_testing ()

add_subdirectory (src)
add_subdirectory (include)
add_subdirectory (examples)
