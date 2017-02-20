cmake_minimum_required(VERSION 3.7)
project(libderp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_definitions(-Wall -Wextra -Werror)

set(HEADER_FILES
        include/libderp/derpexcept.hpp
        include/libderp/endian.hpp
        include/libderp/IRetroDataStream.hpp
        include/libderp/FileRetroDataStream.hpp
        include/libderp/BufferRetroDataStream.hpp
        include/libderp/IBinarySerializable.hpp
        include/libderp/libderp.hpp
        )

set(SOURCE_FILES
        src/IRetroDataStream/IRetroDataStream.cpp
        src/IRetroDataStream/FileRetroDataStream.cpp
        src/IRetroDataStream/BufferRetroDataStream.cpp
        src/libderp.cpp)

add_library(libderp ${SOURCE_FILES} ${HEADER_FILES})