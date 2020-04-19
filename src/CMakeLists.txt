# set (target_name "ms_keychain_gamer")
add_executable(ms_keychain_gamer)

add_subdirectory(drivers)

target_link_libraries(ms_keychain_gamer
    PUBLIC
        hal
        msos_main
        gamer_drivers
)

include (GenerateBinary)
generate_binary(ms_keychain_gamer ${vendor})

target_sources(ms_keychain_gamer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# target_link_libraries(${target_name}
#     PRIVATE
#         msos
#         eul
# )

# include(GenerateBinary)
# generate_binary(${target_name} ${vendor})

# if (NOT DISABLE_SIMULATION)
#     add_custom_command(TARGET ms_keychain_gamer POST_BUILD
#         COMMAND "${CMAKE_COMMAND}" -E copy
#             "$<TARGET_FILE:ms_keychain_gamer>"
#             "${CMAKE_BINARY_DIR}/simulators/$<TARGET_FILE_NAME:ms_keychain_gamer>"
#         COMMAND "${CMAKE_COMMAND}" -E copy
#             "$<TARGET_FILE:ms_keychain_gamer>"
#             "${CMAKE_BINARY_DIR}/$<TARGET_FILE_NAME:ms_keychain_gamer>"
#         COMMENT "Copying to output directory")
# endif ()


