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

add_library(gamer_space_invaders)

target_sources(gamer_space_invaders
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/bullet.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/player.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/bullet.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/player.cpp
)

target_include_directories(gamer_space_invaders
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src/games/space_invaders
        ${PROJECT_SOURCE_DIR}/src
)

target_compile_options(gamer_space_invaders
    PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-std=c++2a>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
    PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:-Werror -Wall -Wextra -Wpedantic -Wcast-align -Wunused -Wshadow -Wpointer-arith -Wcast-qual -Wno-missing-braces>
)

target_link_libraries(gamer_space_invaders
    PRIVATE
        hal_flags
        msgui
        msos
        msos_syscalls
        hal
)
