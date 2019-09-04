set (target_name "ms_keychain_gamer")
add_executable(${target_name})

target_sources(${target_name}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${target_name}
    PRIVATE
        msos
)