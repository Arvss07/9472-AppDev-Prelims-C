cmake_minimum_required(VERSION 3.22)
project(Citizen C)

set(CMAKE_C_STANDARD 11)

add_executable(Citizen main.c
        citizen/citizen.h
        citizen/citizen.c
        file/file.h
        file/file.c
        cmd/terminal_utils.c
        cmd/terminal_utils.h
        utils/util.c
        utils/util.h
        menu/menu.c
        menu/menu.h
)
