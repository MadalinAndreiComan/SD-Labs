cmake_minimum_required(VERSION 3.26)
project(ex1 C)

set(CMAKE_C_STANDARD 23)

add_executable(ex1 ../utils.h main.c
        lab2_utils.c
        lab2_utils.h)
