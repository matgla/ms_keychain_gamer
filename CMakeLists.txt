cmake_minimum_required(VERSION 3.9)

project(MsKeychainGamer_path NONE)

set (CMAKE_EXPORT_COMPILE_COMMANDS true)

include (cmake/GitModules.cmake)

set (user_boards_path ${PROJECT_SOURCE_DIR}/boards CACHE STRING "Path to boards provided from user" FORCE)
fetch_module_via_branch(lib/msos ${PROJECT_SOURCE_DIR}/lib/msos ${CMAKE_CURRENT_SOURCE_DIR} "master")

project(MsKeychainGamer CXX)

if (NOT MS_KEYCHAIN_GAMER_BUILD_TESTS)
    message (STATUS "Building: target")
    add_subdirectory(src)

else ()
    message (STATUS "Building: test")
endif ()