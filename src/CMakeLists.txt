cmake_minimum_required(VERSION 3.18)

include_directories(.)

add_library(interface STATIC)

target_sources(interface PUBLIC
    aegis/types.h
    interface/application.cpp
    interface/application.h
    secret/keys_bank.cpp
    secret/keys_bank.h
    virtfs/path.h
    virtfs/directory.cpp
    virtfs/directory.h
    virtfs/storage.cpp
    virtfs/storage.h
)
