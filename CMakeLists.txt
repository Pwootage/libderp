cmake_minimum_required(VERSION 3.6)
project(libderp)

set(CMAKE_CXX_STANDARD 14)

# ext deps
add_subdirectory(ext/nod)
include_directories(${LOGVISOR_INCLUDE_DIR})
include_directories(ext/nod/include)

# Compiler flags
add_definitions(-Wall -Wextra -Werror -Wno-unused-parameter)

# Source Files
include_directories(include)

set(HEADER_FILES
        include/libderp/derpexcept.hpp
        include/libderp/endian.hpp
        include/libderp/IDataStream.hpp
        include/libderp/FileDataStream.hpp
        include/libderp/BufferDataStream.hpp
        include/libderp/ViewDataStream.hpp
        include/libderp/IBinarySerializable.hpp
        include/libderp/libderp.hpp
        )

set(SOURCE_FILES
        src/IRetroDataStream/IDataStream.cpp
        src/IRetroDataStream/FileDataStream.cpp
        src/IRetroDataStream/BufferDataStream.cpp
        src/IRetroDataStream/ViewDataStream.cpp
        src/libderp.cpp)

# Targets
add_library(derp ${SOURCE_FILES} ${HEADER_FILES})

add_executable(testderp src/test.cpp)
target_link_libraries(testderp
        derp
        logvisor)

# Platform-specific links
if (WIN32)
elseif(APPLE)
#    target_link_libraries(testderp pthread dl)
else ()
    target_link_libraries(testderp pthread dl)
endif ()
