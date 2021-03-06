# This file is part of MSOS project.
# Copyright (C) 2020 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.


add_library(drivers_sfml_simulator STATIC)

target_sources(drivers_sfml_simulator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sfml_simulator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sfml_simulator_file.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_driver.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_driver_file.hpp

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/sfml_simulator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_driver_file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sfml_simulator_file.cpp
)

target_include_directories(drivers_sfml_simulator
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(drivers_sfml_simulator
    PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces>
)

find_package(SFML COMPONENTS graphics REQUIRED)

target_link_libraries(drivers_sfml_simulator
    PRIVATE
        eul
        msos_printer

    PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
        board
)

target_include_directories(drivers_sfml_simulator
    PRIVATE
        ${SFML_INCLUDE_DIR}
)
