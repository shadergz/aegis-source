cmake_minimum_required(VERSION 3.18)

add_library(interface STATIC)
target_sources(interface PUBLIC
    application.cpp
)
