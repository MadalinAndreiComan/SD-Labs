cmake_minimum_required(VERSION 3.26)
project(ex1 C)

set(CMAKE_C_STANDARD 23)

add_executable(ex1 main.c ../../utils.h)
