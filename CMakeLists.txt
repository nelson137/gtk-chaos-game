cmake_minimum_required(VERSION 3.20)

project(ChaosGame)

set(CMAKE_OSX_ARCHITECTURES "arm64")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
link_directories(${GTK4_LIBRARY_DIRS})

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/builder.ui.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/builder.ui
    COMMENT "Generate builder UI header file"
    COMMAND xxd -C -i builder.ui > ${CMAKE_CURRENT_BINARY_DIR}/builder.ui.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_executable(chaos_game
    src/main.c
    src/app.c
    src/model.c
    ${CMAKE_CURRENT_BINARY_DIR}/builder.ui.h
    )

target_link_libraries(chaos_game ${GTK4_LIBRARIES})
