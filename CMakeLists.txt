cmake_minimum_required(VERSION 3.16)
project(Source)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(source STATIC)
add_subdirectory(interface)

target_link_libraries(source PRIVATE interface)
target_include_directories(source PUBLIC interface)
