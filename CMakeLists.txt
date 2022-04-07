cmake_minimum_required(VERSION 3.20)

project(ChaosGame)

set(CMAKE_OSX_ARCHITECTURES "arm64")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

find_program(GLIB_COMPILE_RES NAMES glib-compile-resources REQUIRED)

include_directories(${GTK4_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
link_directories(${GTK4_LIBRARY_DIRS})

set(GRES_BASE chaos_game.gresource)
set(GRES_DEF ${GRES_BASE}.xml)
set(GRES_DEF_IN ${GRES_DEF}.in)
set(GRES_C ${GRES_BASE}.c)
set(GRES_DEPS CACHE INTERNAL "")

set(OLD ${CMAKE_CURRENT_SOURCE_DIR}/${GRES_DEF_IN})
set(NEW ${CMAKE_CURRENT_BINARY_DIR}/${GRES_DEF})

if(NOT EXISTS ${NEW} OR ${OLD} IS_NEWER_THAN ${NEW})
    configure_file(${GRES_DEF_IN} ${GRES_DEF})
    execute_process(
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${GLIB_COMPILE_RES} --generate-dependencies ${GRES_DEF}
        OUTPUT_VARIABLE GRES_DEPS
        )
    string(REPLACE "\n" ";" GRES_DEPS ${GRES_DEPS})
    list(POP_BACK GRES_DEPS)
    list(TRANSFORM GRES_DEPS PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/resource/)
endif()

add_custom_command(
    OUTPUT ${GRES_C}
    MAIN_DEPENDENCY ${GRES_DEF}
    DEPENDS ${GRES_DEPS}
    COMMENT "Generate resources"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resource
    COMMAND ${GLIB_COMPILE_RES}
    ARGS -C ${CMAKE_C_COMPILER} --generate --target=${CMAKE_CURRENT_BINARY_DIR}/${GRES_C} ${NEW}
    VERBATIM
    )

add_custom_target(GenerateResources DEPENDS ${GRES_C})

add_executable(chaos_game
    src/main.c
    src/app.c
    src/model.c
    src/util.c
    ${GRES_C}
    )

add_dependencies(chaos_game GenerateResources)

target_link_libraries(chaos_game ${GTK4_LIBRARIES})
