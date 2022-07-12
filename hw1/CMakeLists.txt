cmake_minimum_required(VERSION 3.22)
project(1_nd C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(1_nd
        functions.c
        functions.h
        test.c
        )

