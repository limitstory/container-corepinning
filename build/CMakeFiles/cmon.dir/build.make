# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/limitstory/workspace/cmonitor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/limitstory/workspace/cmonitor/build

# Include any dependencies generated for this target.
include CMakeFiles/cmon.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmon.dir/flags.make

CMakeFiles/cmon.dir/cmon/main.c.o: CMakeFiles/cmon.dir/flags.make
CMakeFiles/cmon.dir/cmon/main.c.o: ../cmon/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/limitstory/workspace/cmonitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmon.dir/cmon/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cmon.dir/cmon/main.c.o   -c /home/limitstory/workspace/cmonitor/cmon/main.c

CMakeFiles/cmon.dir/cmon/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cmon.dir/cmon/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/limitstory/workspace/cmonitor/cmon/main.c > CMakeFiles/cmon.dir/cmon/main.c.i

CMakeFiles/cmon.dir/cmon/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cmon.dir/cmon/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/limitstory/workspace/cmonitor/cmon/main.c -o CMakeFiles/cmon.dir/cmon/main.c.s

CMakeFiles/cmon.dir/cmon/main.c.o.requires:

.PHONY : CMakeFiles/cmon.dir/cmon/main.c.o.requires

CMakeFiles/cmon.dir/cmon/main.c.o.provides: CMakeFiles/cmon.dir/cmon/main.c.o.requires
	$(MAKE) -f CMakeFiles/cmon.dir/build.make CMakeFiles/cmon.dir/cmon/main.c.o.provides.build
.PHONY : CMakeFiles/cmon.dir/cmon/main.c.o.provides

CMakeFiles/cmon.dir/cmon/main.c.o.provides.build: CMakeFiles/cmon.dir/cmon/main.c.o


# Object files for target cmon
cmon_OBJECTS = \
"CMakeFiles/cmon.dir/cmon/main.c.o"

# External object files for target cmon
cmon_EXTERNAL_OBJECTS =

cmon: CMakeFiles/cmon.dir/cmon/main.c.o
cmon: CMakeFiles/cmon.dir/build.make
cmon: libdocker.so
cmon: CMakeFiles/cmon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/limitstory/workspace/cmonitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cmon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmon.dir/build: cmon

.PHONY : CMakeFiles/cmon.dir/build

CMakeFiles/cmon.dir/requires: CMakeFiles/cmon.dir/cmon/main.c.o.requires

.PHONY : CMakeFiles/cmon.dir/requires

CMakeFiles/cmon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmon.dir/clean

CMakeFiles/cmon.dir/depend:
	cd /home/limitstory/workspace/cmonitor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/limitstory/workspace/cmonitor /home/limitstory/workspace/cmonitor /home/limitstory/workspace/cmonitor/build /home/limitstory/workspace/cmonitor/build /home/limitstory/workspace/cmonitor/build/CMakeFiles/cmon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmon.dir/depend
