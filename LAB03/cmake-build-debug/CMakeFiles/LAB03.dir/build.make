# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/67/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/67/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/grzegorz/Dokumenty/Grafika/LAB03

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/grzegorz/Dokumenty/Grafika/LAB03/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LAB03.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LAB03.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LAB03.dir/flags.make

CMakeFiles/LAB03.dir/main.cpp.o: CMakeFiles/LAB03.dir/flags.make
CMakeFiles/LAB03.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/grzegorz/Dokumenty/Grafika/LAB03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LAB03.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LAB03.dir/main.cpp.o -c /home/grzegorz/Dokumenty/Grafika/LAB03/main.cpp

CMakeFiles/LAB03.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LAB03.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/grzegorz/Dokumenty/Grafika/LAB03/main.cpp > CMakeFiles/LAB03.dir/main.cpp.i

CMakeFiles/LAB03.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LAB03.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/grzegorz/Dokumenty/Grafika/LAB03/main.cpp -o CMakeFiles/LAB03.dir/main.cpp.s

# Object files for target LAB03
LAB03_OBJECTS = \
"CMakeFiles/LAB03.dir/main.cpp.o"

# External object files for target LAB03
LAB03_EXTERNAL_OBJECTS =

LAB03: CMakeFiles/LAB03.dir/main.cpp.o
LAB03: CMakeFiles/LAB03.dir/build.make
LAB03: CMakeFiles/LAB03.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/grzegorz/Dokumenty/Grafika/LAB03/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LAB03"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LAB03.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LAB03.dir/build: LAB03

.PHONY : CMakeFiles/LAB03.dir/build

CMakeFiles/LAB03.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LAB03.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LAB03.dir/clean

CMakeFiles/LAB03.dir/depend:
	cd /home/grzegorz/Dokumenty/Grafika/LAB03/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/grzegorz/Dokumenty/Grafika/LAB03 /home/grzegorz/Dokumenty/Grafika/LAB03 /home/grzegorz/Dokumenty/Grafika/LAB03/cmake-build-debug /home/grzegorz/Dokumenty/Grafika/LAB03/cmake-build-debug /home/grzegorz/Dokumenty/Grafika/LAB03/cmake-build-debug/CMakeFiles/LAB03.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LAB03.dir/depend
