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
CMAKE_SOURCE_DIR = /home/zhongchen/dfw_workshop

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhongchen/dfw_workshop/build

# Include any dependencies generated for this target.
include DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/depend.make

# Include the progress variables for this target.
include DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/progress.make

# Include the compile flags for this target's objects.
include DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/flags.make

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o: DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/flags.make
DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o: ../DFW_Workshop/pmem_recovery_simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhongchen/dfw_workshop/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o"
	cd /home/zhongchen/dfw_workshop/build/DFW_Workshop && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o -c /home/zhongchen/dfw_workshop/DFW_Workshop/pmem_recovery_simulation.cpp

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.i"
	cd /home/zhongchen/dfw_workshop/build/DFW_Workshop && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhongchen/dfw_workshop/DFW_Workshop/pmem_recovery_simulation.cpp > CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.i

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.s"
	cd /home/zhongchen/dfw_workshop/build/DFW_Workshop && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhongchen/dfw_workshop/DFW_Workshop/pmem_recovery_simulation.cpp -o CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.s

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.requires:

.PHONY : DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.requires

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.provides: DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.requires
	$(MAKE) -f DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/build.make DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.provides.build
.PHONY : DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.provides

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.provides.build: DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o


# Object files for target pmem_recovery_simulation
pmem_recovery_simulation_OBJECTS = \
"CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o"

# External object files for target pmem_recovery_simulation
pmem_recovery_simulation_EXTERNAL_OBJECTS =

DFW_Workshop/pmem_recovery_simulation: DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o
DFW_Workshop/pmem_recovery_simulation: DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/build.make
DFW_Workshop/pmem_recovery_simulation: DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhongchen/dfw_workshop/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pmem_recovery_simulation"
	cd /home/zhongchen/dfw_workshop/build/DFW_Workshop && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pmem_recovery_simulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/build: DFW_Workshop/pmem_recovery_simulation

.PHONY : DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/build

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/requires: DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/pmem_recovery_simulation.cpp.o.requires

.PHONY : DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/requires

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/clean:
	cd /home/zhongchen/dfw_workshop/build/DFW_Workshop && $(CMAKE_COMMAND) -P CMakeFiles/pmem_recovery_simulation.dir/cmake_clean.cmake
.PHONY : DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/clean

DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/depend:
	cd /home/zhongchen/dfw_workshop/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhongchen/dfw_workshop /home/zhongchen/dfw_workshop/DFW_Workshop /home/zhongchen/dfw_workshop/build /home/zhongchen/dfw_workshop/build/DFW_Workshop /home/zhongchen/dfw_workshop/build/DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : DFW_Workshop/CMakeFiles/pmem_recovery_simulation.dir/depend
