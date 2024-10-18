# Raylib is a C library that provides a simple way to create GUI applications particularly used
# for game development.

# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.22)

# Define the project name and specify the language
project(Citizen C)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)  # Ensure C11 is required

# Optional: Set the output directory for executable
# ${CMAKE_BINARY_DIR} -> the top-level directory of the build tree
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/storeHere)

# Try to find the Raylib package quietly
# QUIET : Do not print any messages
find_package(raylib QUIET)

# If Raylib is not found, fetch and download it
if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG        4.0.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Collect source files and save them in a variable called SOURCE_FILES
set(SOURCE_FILES
        main.c
        citizen/citizen.c
        file/file.c
        cmd/terminal_utils.c
        utils/util.c
        raylib_sample/loadWindow.c
)

# Create the executable target using the collected source files
add_executable(Citizen ${SOURCE_FILES})

# Link the Raylib library to the Citizen executable
target_link_libraries(Citizen raylib)

# Include directories for header files
# PRIVATE : Only Citizen target can access these directories and not other targets
target_include_directories(Citizen PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/citizen
        ${CMAKE_CURRENT_SOURCE_DIR}/file
        ${CMAKE_CURRENT_SOURCE_DIR}/cmd
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/raylib_sample
)

# Optional: Add a message to indicate successful configuration
message(STATUS "CMake configuration complete. Building project: ${PROJECT_NAME}")