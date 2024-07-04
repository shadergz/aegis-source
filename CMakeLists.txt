cmake_minimum_required(VERSION 3.16)
project(Source)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_libraries(source STATIC)
target_sources(
    application.cpp
)
