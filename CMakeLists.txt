cmake_minimum_required(VERSION 2.8)
project(TeslaCo CXX)

set(CXX_FLAGS
 -O2
 -g
 -pg
 -Wall
 -Wextra
 -Werror
 -std=c++11
 -pthread
)

include_directories(${PROJECT_SOURCE_DIR}/src)

find_package(Threads REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(test)
add_subdirectory(src)