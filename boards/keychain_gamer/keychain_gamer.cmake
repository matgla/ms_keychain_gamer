function(get_device_info mcu mcu_family arch vendor)
    message(STATUS "Configuration of board: KeychainGamer")
    set(${mcu} "attiny85" PARENT_SCOPE)
    set(${mcu_family} "ATTINY" PARENT_SCOPE)
    set(${arch} "AVR" PARENT_SCOPE)
    set(${vendor} "ATMEL" PARENT_SCOPE)
endfunction()

function(add_device_hal_library hal_device_library)
    set(${hal_device_library} "avr_keychain_gamer")
    set(hal_device_library ${hal_device_library} PARENT_SCOPE)
    add_library(${hal_device_library} INTERFACE)

    target_sources(${hal_device_library} INTERFACE
        ${user_boards_path}/keychain_gamer/board.hpp
    )

    target_include_directories(${hal_device_library} INTERFACE
        ${user_boards_path}/keychain_gamer)

    add_subdirectory(${PROJECT_SOURCE_DIR}/src/avr)

    target_link_libraries(${hal_device_library}
        INTERFACE
            hal_interface
            hal_avr
    )
endfunction()