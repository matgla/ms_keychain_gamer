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

add_library(gamer_drivers INTERFACE)

add_subdirectory(gamepad)

if (ENABLE_KEYBOARD)
    add_subdirectory(keyboard)
endif ()

if (ENABLE_DRIVERS_SFML_SIMULATOR)
    add_subdirectory(sfml_simulator)
endif()

if (ENABLE_DRIVERS_LINUX_AUDIO)
    add_subdirectory(linux_audio)
endif()
