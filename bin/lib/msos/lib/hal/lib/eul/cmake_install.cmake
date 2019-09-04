# Install script for directory: /mnt/c/data/repos/ms_keychain_gamer/lib/msos/lib/hal/lib/eul

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/mnt/c/data/repos/ms_keychain_gamer/bin/libeul.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/mnt/c/data/repos/ms_keychain_gamer/bin" TYPE STATIC_LIBRARY FILES "/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/libeul.a")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/lib/cmake_install.cmake")
  include("/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/source/logger/cmake_install.cmake")
  include("/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/source/utils/cmake_install.cmake")
  include("/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/include/eul/execution/cmake_install.cmake")
  include("/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/include/eul/time/cmake_install.cmake")
  include("/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/include/eul/timer/cmake_install.cmake")
  include("/mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/include/eul/mpl/cmake_install.cmake")

endif()

