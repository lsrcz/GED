cmake_minimum_required(VERSION 3.10)
project(GED)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "-O0")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-march=native -frename-registers -funroll-loops -finline-functions -O3")
endif ()

include_directories(include)
add_executable(GED src/main.cpp src/input.cpp src/lsap.cpp src/lsape.cpp include/lsape.h)
add_executable(test_lsape src/lsape.cpp include/lsape.h test/test_lsape.cpp src/lsap.cpp include/lsap.h)
