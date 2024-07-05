cmake_minimum_required(VERSION 3.16)

project(Source CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(source STATIC)
add_subdirectory(src)

target_link_libraries(source PUBLIC interface)

target_include_directories(source PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:>
)

if(ANDROID)
    add_subdirectory(android/app/src/main/jni)
    target_include_directories(source PRIVATE android/app/src/jni)
endif()
