add_executable(keychain_gamer_simulator)

target_sources(keychain_gamer_simulator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/simulation.cpp
)

target_link_libraries(keychain_gamer_simulator
    PRIVATE
        simavr
        elf)