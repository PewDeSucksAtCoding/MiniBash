cmake_minimum_required(VERSION 4.1)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(MiniBash main.c
        parser.h
        parser.c
        executor.h
        executor.c)
