# This file is part of MS keychain gamer project.
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

add_library(gamer_drivers_gamepad)

target_sources(gamer_drivers_gamepad
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/event.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gamepad_driver.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gamepad_file.hpp

    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/gamepad_driver.cpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/gamepad_file.cpp
)

target_include_directories(gamer_drivers_gamepad
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(gamer_drivers_gamepad
    PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces>
)

target_link_libraries(gamer_drivers_gamepad
    PUBLIC
        board
        msos_interface
        hal_flags
)

target_link_libraries(gamer_drivers
    INTERFACE
        gamer_drivers_gamepad
)
