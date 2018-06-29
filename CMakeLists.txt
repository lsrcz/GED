cmake_minimum_required(VERSION 3.10)
project(GED)

set(CMAKE_CXX_STANDARD 11)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "-O0 -g -fsanitize=address -fno-omit-frame-pointer")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "-march=native -frename-registers -funroll-loops -finline-functions -fopenmp -Ofast")
endif ()

if (ENABLE_DEBUG_OUTPUT MATCHES True)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

include_directories(include)
add_executable(GED
        src/main.cpp
        src/chemgraph.cpp
        src/lsap.cpp
        src/quadratic.cpp
        src/lsape.cpp
        src/costMat.cpp
        src/utils.cpp
        src/IPFP.cpp
        src/init.cpp
        src/dataset.cpp)
add_executable(test_lsape
        src/lsape.cpp
        test/test_lsape.cpp
        src/lsap.cpp
        src/utils.cpp)
add_executable(test_dataset
        src/dataset.cpp
        test/test_dataset.cpp
        src/IPFP.cpp
        src/init.cpp
        src/costMat.cpp
        src/chemgraph.cpp
        src/utils.cpp
        src/quadratic.cpp
        src/lsape.cpp)
