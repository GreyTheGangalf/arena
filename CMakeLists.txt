cmake_minimum_required(VERSION 3.25)
project(arena LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # clang-tidy and Qt Creator read this

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# raylib is downloaded and built with the project, so no system install is needed.
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
    GIT_SHALLOW    TRUE
    SYSTEM         # raylib headers do not trigger our warnings or clang-tidy
)
FetchContent_MakeAvailable(raylib)

add_executable(arena src/main.cpp)
target_link_libraries(arena PRIVATE raylib)

if(MSVC)
    target_compile_options(arena PRIVATE /W4)
else()
    target_compile_options(arena PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

if(APPLE)
    target_link_libraries(arena PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()
