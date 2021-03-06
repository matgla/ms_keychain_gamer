add_executable(ms_keychain_gamer)

add_subdirectory(drivers)
add_subdirectory(games)
add_subdirectory(io)

target_link_libraries(ms_keychain_gamer
    PRIVATE
        hal
        msos
        msos_main
        gamer_drivers
        gamer_io
        gamer_space_invaders
        synth
)

include (GenerateBinary)
generate_binary(ms_keychain_gamer ${vendor})

target_sources(ms_keychain_gamer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

if (NOT DISABLE_SIMULATION)
    add_custom_command(TARGET ms_keychain_gamer POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:ms_keychain_gamer>"
            "${CMAKE_BINARY_DIR}/simulators/$<TARGET_FILE_NAME:ms_keychain_gamer>"
        COMMAND "${CMAKE_COMMAND}" -E copy
            "$<TARGET_FILE:ms_keychain_gamer>"
            "${CMAKE_BINARY_DIR}/$<TARGET_FILE_NAME:ms_keychain_gamer>"
        COMMENT "Copying to output directory")
endif ()


