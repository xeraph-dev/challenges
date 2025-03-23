# Copyright 2024 xeraph. All rights reserved. Use of this source code is
# governed by a BSD-style license that can be found in the LICENSE file.

cmake_minimum_required(VERSION 3.28)

project(
    pong
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_C_EXTENSIONS off)

find_package(raylib 5.5)

add_executable(
    ${PROJECT_NAME}
    src/main.c
    src/ball.c
    src/game.c
    src/paddle.c
    src/screen.c
    src/screens/gameplay.c
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE -Weverything
            -Werror
            -pedantic
            -Wno-declaration-after-statement
            -Wno-padded
            -Wno-switch-default
            -ferror-limit=0
            -fdiagnostics-color
)
target_compile_definitions(
    ${PROJECT_NAME} PUBLIC PROJECT_NAME="${PROJECT_NAME}"
                           PROJECT_VERSION="${PROJECT_VERSION}"
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
)

add_custom_target(
    run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
