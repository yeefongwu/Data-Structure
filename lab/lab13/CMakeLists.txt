cmake_minimum_required(VERSION 3.19)
project(lab13)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab13
        ds_smart_pointers.h
        check2.cpp
        check3.cpp)
