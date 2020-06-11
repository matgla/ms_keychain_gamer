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

add_executable(synthlib_tests)

target_sources(synthlib_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/envelope_tests.cpp
)

target_link_libraries(synthlib_tests
    PRIVATE
        gtest
        gtest_main
        gmock
        synthlib
)

add_test(synthlib_tests synthlib_tests)

add_dependencies(build_and_test synthlib_tests)
