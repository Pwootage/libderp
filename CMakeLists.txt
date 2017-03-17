cmake_minimum_required(VERSION 3.6)
project(libderp)

set(CMAKE_CXX_STANDARD 14)

# ext deps
add_subdirectory(ext/nod)
include_directories(${LOGVISOR_INCLUDE_DIR})
include_directories(ext/nod/include)

add_subdirectory(ext/glm)
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# Compiler flags
add_definitions(-Wall -Wextra -Werror -Wno-unused-parameter)
# TODO: remove when complete
add_definitions(-Wno-error=unused-variable)

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
        include/libderp/prime1/MREA.hpp
        )

set(SOURCE_FILES
        src/IDataStream/IDataStream.cpp
        src/IDataStream/IDataStreamRead.cpp
        src/IDataStream/IDataStreamWrite.cpp
        src/IDataStream/FileDataStream.cpp
        src/IDataStream/BufferDataStream.cpp
        src/IDataStream/ViewDataStream.cpp
        src/prime1/MREA.cpp
        )

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
