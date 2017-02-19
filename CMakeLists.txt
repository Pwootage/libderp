cmake_minimum_required(VERSION 3.7)
project(libderp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES
        src/libderp.cpp)

add_library(libderp ${SOURCE_FILES})