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
CMAKE_COMMAND = /opt/clion-2018.3.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.3.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Desktop/HTSim/HTsim_Starlink/sim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Desktop/HTSim/HTsim_Starlink/sim/cmake-build-debug

# Utility rule file for buildHTSim.

# Include the progress variables for this target.
include CMakeFiles/buildHTSim.dir/progress.make

CMakeFiles/buildHTSim:
	cd /home/user/Desktop/HTSim/HTsim_Starlink/sim && make

buildHTSim: CMakeFiles/buildHTSim
buildHTSim: CMakeFiles/buildHTSim.dir/build.make

.PHONY : buildHTSim

# Rule to build all files generated by this target.
CMakeFiles/buildHTSim.dir/build: buildHTSim

.PHONY : CMakeFiles/buildHTSim.dir/build

CMakeFiles/buildHTSim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/buildHTSim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/buildHTSim.dir/clean

CMakeFiles/buildHTSim.dir/depend:
	cd /home/user/Desktop/HTSim/HTsim_Starlink/sim/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/Desktop/HTSim/HTsim_Starlink/sim /home/user/Desktop/HTSim/HTsim_Starlink/sim /home/user/Desktop/HTSim/HTsim_Starlink/sim/cmake-build-debug /home/user/Desktop/HTSim/HTsim_Starlink/sim/cmake-build-debug /home/user/Desktop/HTSim/HTsim_Starlink/sim/cmake-build-debug/CMakeFiles/buildHTSim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/buildHTSim.dir/depend

