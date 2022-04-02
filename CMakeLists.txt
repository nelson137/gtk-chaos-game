cmake_minimum_required(VERSION 3.20)

project(ChaosGame)

set(CMAKE_OSX_ARCHITECTURES "arm64")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_executable(chaos_game
    src/main.c
    )

target_link_libraries(chaos_game ${GTK4_LIBRARIES})
