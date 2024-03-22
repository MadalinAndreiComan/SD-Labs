cmake_minimum_required(VERSION 3.26)
project(Ex1 C)

set(CMAKE_C_STANDARD 23)

add_executable(Ex1 main.c
        lab3_ex1_utils.c
        lab3_ex1_utils.h)
