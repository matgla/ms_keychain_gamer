# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.14.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.14.0-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/data/repos/ms_keychain_gamer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/data/repos/ms_keychain_gamer/bin

# Include any dependencies generated for this target.
include lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/depend.make

# Include the progress variables for this target.
include lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/progress.make

# Include the compile flags for this target's objects.
include lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/flags.make

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/math.cpp.o: lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/flags.make
lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/math.cpp.o: ../lib/msos/lib/hal/lib/eul/source/utils/math.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/data/repos/ms_keychain_gamer/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/math.cpp.o"
	cd /mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/source/utils && /usr/local/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eul_utils.dir/math.cpp.o -c /mnt/c/data/repos/ms_keychain_gamer/lib/msos/lib/hal/lib/eul/source/utils/math.cpp

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/math.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eul_utils.dir/math.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/math.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eul_utils.dir/math.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/string.cpp.o: lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/flags.make
lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/string.cpp.o: ../lib/msos/lib/hal/lib/eul/source/utils/string.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/data/repos/ms_keychain_gamer/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/string.cpp.o"
	cd /mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/source/utils && /usr/local/bin/avr-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eul_utils.dir/string.cpp.o -c /mnt/c/data/repos/ms_keychain_gamer/lib/msos/lib/hal/lib/eul/source/utils/string.cpp

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/string.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eul_utils.dir/string.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/string.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eul_utils.dir/string.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

eul_utils: lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/math.cpp.o
eul_utils: lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/string.cpp.o
eul_utils: lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/build.make

.PHONY : eul_utils

# Rule to build all files generated by this target.
lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/build: eul_utils

.PHONY : lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/build

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/clean:
	cd /mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/source/utils && $(CMAKE_COMMAND) -P CMakeFiles/eul_utils.dir/cmake_clean.cmake
.PHONY : lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/clean

lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/depend:
	cd /mnt/c/data/repos/ms_keychain_gamer/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/data/repos/ms_keychain_gamer /mnt/c/data/repos/ms_keychain_gamer/lib/msos/lib/hal/lib/eul/source/utils /mnt/c/data/repos/ms_keychain_gamer/bin /mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/source/utils /mnt/c/data/repos/ms_keychain_gamer/bin/lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/msos/lib/hal/lib/eul/source/utils/CMakeFiles/eul_utils.dir/depend

