cmake_minimum_required(VERSION 3.18)

include_directories(.)

add_library(interface STATIC)

target_sources(interface PUBLIC
    base/types.h
    base/exception.cpp
    base/exception.h
    interface/application.cpp
    interface/application.h
    secret/keys_bank.cpp
    secret/keys_bank.h
    secret/encode.h
    virtfs/path.h
    virtfs/directory.cpp
    virtfs/directory.h
    virtfs/os_accessor.h
    virtfs/device_backing.cpp
    virtfs/device_stream.h
    virtfs/device_stream.cpp
    virtfs/device_stream.h
    host/barrier.h
)
target_link_libraries(interface PUBLIC fmt::fmt)
