cmake_minimum_required(VERSION 3.16)

add_library(interface STATIC)
target_sources(interface PUBLIC
    application.cpp
    application.h
)
