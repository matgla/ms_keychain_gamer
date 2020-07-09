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

add_library(synthlib)

target_sources(synthlib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/instruments/bell.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscillators/oscillator.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscillators/sine.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/channel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/envelope.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/instrument.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/note_frequency.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/note.hpp

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/instruments/bell.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/oscillators/sine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/channel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/envelope.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/note_frequency.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/note.cpp
)

target_include_directories(synthlib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src/games
        ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(synthlib
    PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces>
)

target_link_libraries(synthlib
    PUBLIC
        board
        msos_interface
        hal_flags
)
