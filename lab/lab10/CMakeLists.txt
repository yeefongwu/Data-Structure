cmake_minimum_required(VERSION 3.19)
project(lab10)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab10
        ds_set.h
        test_ds_set.cpp)
