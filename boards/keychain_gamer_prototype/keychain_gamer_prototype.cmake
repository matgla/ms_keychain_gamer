function(get_device_info mcu mcu_family arch vendor)
    message(STATUS "Configuration of board: KeychainGamer")
    set(${mcu} "atmega8" PARENT_SCOPE)
    set(${mcu_family} "ATMEGA" PARENT_SCOPE)
    set(${arch} "AVR" PARENT_SCOPE)
    set(${vendor} "ATMEL" PARENT_SCOPE)
endfunction()

function(add_device_hal_library hal_device_library)
    set(${hal_device_library} "avr_keychain_gamer")
    set(hal_device_library ${hal_device_library} PARENT_SCOPE)
    add_library(${hal_device_library} INTERFACE)

    target_sources(${hal_device_library} INTERFACE
        ${user_boards_path}/keychain_gamer_prototype/board.hpp
    )

    target_include_directories(${hal_device_library} INTERFACE
        ${user_boards_path}/keychain_gamer_prototype)

    include(${PROJECT_SOURCE_DIR}/devices/avr/atmega/atmega8/CMakeLists.cmake)

    target_link_libraries(${hal_device_library}
        INTERFACE
            hal_interface
            hal_devices_avr_atmega8
    )
endfunction()