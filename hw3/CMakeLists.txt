cmake_minimum_required(VERSION 3.22)
project(hw3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hw3
        cashier.c
        cashier.h
        customer.c
        customer.h
        main.c
        pqueue.c
        pqueue.h
        queue.c
        queue.h)
