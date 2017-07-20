cmake_minimum_required(VERSION 3.0)

project(po CXX)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=gnu++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14) 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
else()
    message(FATAL_ERROR
        "${CMAKE_CXX_COMPILER} はC++14をサポートしてません。
C++14に対応したコンパイラを指定してください。
EXAMPLE:
    $ cmake . -DCMAKE_CXX_COMPILER=/usr/bin/g++-5.4")
endif()
message("Compiler:\n\t${CMAKE_CXX_COMPILER}")

# Set default build type to Release
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set compile flags
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wswitch-default -Wdisabled-optimization -Wformat -Winit-self -Woverloaded-virtual -Wfloat-equal -lm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-old-style-cast -Wno-pragmas")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# OpenCV
if(JETSON_CROSS)
    file(GLOB OpenCV_LIBS "$ENV{HOME}/.robotech/jetson_cross/lib/libopencv*.so")
else()
    find_package(OpenCV REQUIRED)
    message("OpenCV:\n\t${OpenCV_INCLUDE_DIRS}")
    include_directories(SYSTEM ${OpenCV_INCLUDE_DIR})
endif()

# OpenGL
find_package(GLUT)
find_package(OpenGL)

# src/ and include/
file(GLOB_RECURSE SUB_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

# Sources and headers
file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
list(APPEND SOURCES ${SUB_SOURCES})
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Echo compile flags
message("Build type:\n\t${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Compile flags:\n\t${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Compile flags:\n\t${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
else()
    message("Compile flags:\n\t${CMAKE_CXX_FLAGS}")
endif()

# Build main
add_executable(main ${SOURCES})
target_link_libraries(main
    ${GLUT_LIBRARY}
    ${OPENGL_LIBRARY}
    ${OpenCV_LIBS}
    pthread)

# ClangFormat
add_custom_target(format
    COMMAND git ls-files `git rev-parse --show-toplevel` | grep \"[ch]pp\" | xargs clang-format -style=file -i)

# Clean
add_custom_target(cmake-clean
    COMMAND rm -rf `find ${CMAKE_BINARY_DIR} -name \"*[cC][mM]ake*\" -and -not -name \"CMakeLists.txt\"`
    COMMAND rm -rf `find ${CMAKE_BINARY_DIR} -name \"Makefile\"`)

add_custom_target(full-clean
    COMMAND make clean
    COMMAND make cmake-clean)
