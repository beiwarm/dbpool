# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/Work/mysql_pool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Work/mysql_pool/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mysql_pool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mysql_pool.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mysql_pool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mysql_pool.dir/flags.make

CMakeFiles/mysql_pool.dir/main.cpp.o: CMakeFiles/mysql_pool.dir/flags.make
CMakeFiles/mysql_pool.dir/main.cpp.o: ../main.cpp
CMakeFiles/mysql_pool.dir/main.cpp.o: CMakeFiles/mysql_pool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Work/mysql_pool/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mysql_pool.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mysql_pool.dir/main.cpp.o -MF CMakeFiles/mysql_pool.dir/main.cpp.o.d -o CMakeFiles/mysql_pool.dir/main.cpp.o -c /mnt/d/Work/mysql_pool/main.cpp

CMakeFiles/mysql_pool.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mysql_pool.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Work/mysql_pool/main.cpp > CMakeFiles/mysql_pool.dir/main.cpp.i

CMakeFiles/mysql_pool.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mysql_pool.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Work/mysql_pool/main.cpp -o CMakeFiles/mysql_pool.dir/main.cpp.s

# Object files for target mysql_pool
mysql_pool_OBJECTS = \
"CMakeFiles/mysql_pool.dir/main.cpp.o"

# External object files for target mysql_pool
mysql_pool_EXTERNAL_OBJECTS =

mysql_pool: CMakeFiles/mysql_pool.dir/main.cpp.o
mysql_pool: CMakeFiles/mysql_pool.dir/build.make
mysql_pool: /usr/lib/x86_64-linux-gnu/libjsoncpp.so.1.9.5
mysql_pool: CMakeFiles/mysql_pool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Work/mysql_pool/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mysql_pool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mysql_pool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mysql_pool.dir/build: mysql_pool
.PHONY : CMakeFiles/mysql_pool.dir/build

CMakeFiles/mysql_pool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mysql_pool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mysql_pool.dir/clean

CMakeFiles/mysql_pool.dir/depend:
	cd /mnt/d/Work/mysql_pool/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Work/mysql_pool /mnt/d/Work/mysql_pool /mnt/d/Work/mysql_pool/cmake-build-debug /mnt/d/Work/mysql_pool/cmake-build-debug /mnt/d/Work/mysql_pool/cmake-build-debug/CMakeFiles/mysql_pool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mysql_pool.dir/depend

