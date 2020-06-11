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

add_library(assets INTERFACE)

include (GenerateImage)

generate_image(assets ${CMAKE_CURRENT_SOURCE_DIR}/main_menu_monster.png ${CMAKE_CURRENT_BINARY_DIR}/assets/main_menu_monster.hpp main_menu_monster space_invaders)
generate_image(assets ${CMAKE_CURRENT_SOURCE_DIR}/main_menu_press_key.png ${CMAKE_CURRENT_BINARY_DIR}/assets/main_menu_press_key.hpp main_menu_press_key space_invaders)
generate_image(assets ${CMAKE_CURRENT_SOURCE_DIR}/main_menu_title.png ${CMAKE_CURRENT_BINARY_DIR}/assets/main_menu_title.hpp main_menu_title space_invaders)

target_include_directories(assets INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
