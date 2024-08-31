cmake_minimum_required(VERSION 3.29)
project(Citizen C)

set(CMAKE_C_STANDARD 11)

add_executable(Citizen main.c
        citizen/citizen.h
        citizen/citizen.c
        file/file.h
        file/file.c
        cmd/terminal_utils.c
        cmd/terminal_utils.h
        sorting/sort.c
        sorting/sort.h)
