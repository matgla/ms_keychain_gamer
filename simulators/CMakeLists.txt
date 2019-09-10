cmake_minimum_required(VERSION 3.2)

project (KeychainGamerSimulator C CXX)

message("BOARD IS: ${BOARD}")
if (${BOARD} STREQUAL "keychain_gamer")
    message (STATUS "Adding simulator for: keychain_gamer")
    add_subdirectory(keychain_gamer)
endif ()