cmake_minimum_required(VERSION 3.9)

project(MsKeychainGamer NONE)

set (CMAKE_EXPORT_COMPILE_COMMANDS true)

include (cmake/GitModules.cmake)

set (user_boards_path ${PROJECT_SOURCE_DIR}/boards CACHE STRING "Path to boards provided from user" FORCE)
fetch_module_via_branch(lib/msos ${PROJECT_SOURCE_DIR}/lib/msos ${CMAKE_CURRENT_SOURCE_DIR} "master")

enable_language(CXX)

if (NOT MS_KEYCHAIN_GAMER_BUILD_TESTS)
    include(SetCompilationSystem)
    set_compilation_target()
    message (STATUS "Building: target")
    add_subdirectory(src)
else ()
    message (STATUS "Building: test")
endif ()

if (NOT DISABLE_SIMULATION)
    message (STATUS "Adding simulators")
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/simulators)
    file(TOUCH ${CMAKE_BINARY_DIR}/simulators/dummy.cpp)
    add_library(dummy STATIC ${CMAKE_BINARY_DIR}/simulators/dummy.cpp)
    add_custom_target(dummy_target
        ALL
        DEPENDS simulators)
    add_custom_command(
        OUTPUT simulators
        COMMAND ${CMAKE_COMMAND} ../..
                -DCMAKE_BUILD_TYPE:STRING="Release"
                -DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE:PATH="${CMAKE_BINARY_DIR}/simulators"
                -H"${PROJECT_SOURCE_DIR}/simulators"
                -DBOARD="${BOARD}"
        COMMAND ${CMAKE_COMMAND} --build . --config Release
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/simulators
        DEPENDS always_rebuild
    )

    add_dependencies(ms_keychain_gamer dummy)
    add_custom_command(
        OUTPUT always_rebuild
        COMMAND cmake -E echo
    )


endif ()