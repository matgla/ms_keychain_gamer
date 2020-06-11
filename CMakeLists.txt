cmake_minimum_required(VERSION 3.9)

project(MsKeychainGamer NONE)

set (CMAKE_EXPORT_COMPILE_COMMANDS true)

include (cmake/GitModules.cmake)

set (user_boards_path ${PROJECT_SOURCE_DIR}/boards CACHE STRING "Path to boards provided from user" FORCE)
fetch_module_via_branch(lib/msos ${PROJECT_SOURCE_DIR}/lib/msos ${CMAKE_CURRENT_SOURCE_DIR} "master")

include_directories(BEFORE SYSTEM ${msos_system_include_directories})

enable_language(CXX C ASM)

if (NOT MS_KEYCHAIN_GAMER_BUILD_TESTS)
    include(SetCompilationSystem)
    set_compilation_target()
    message (STATUS "Building: target")
    add_subdirectory(src)

else ()
    message (STATUS "Building: test")
endif ()

if (NOT MS_KEYCHAIN_GAMER_DISABLE_TESTS)
    message ("Adding UT tests")
    enable_testing()
    add_subdirectory(test/ut)
endif ()
