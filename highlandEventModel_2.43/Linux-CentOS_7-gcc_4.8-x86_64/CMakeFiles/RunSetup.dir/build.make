# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/bin/cmake3

# The command to remove a file.
RM = /usr/bin/cmake3 -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/Linux-CentOS_7-gcc_4.8-x86_64

# Utility rule file for RunSetup.

# Include the progress variables for this target.
include CMakeFiles/RunSetup.dir/progress.make

CMakeFiles/RunSetup: /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/bin/setup.sh
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/Linux-CentOS_7-gcc_4.8-x86_64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) " Source bin/setup.sh to initialise environment etc."
	. ../bin/setup.sh | tee setup.log

RunSetup: CMakeFiles/RunSetup
RunSetup: CMakeFiles/RunSetup.dir/build.make

.PHONY : RunSetup

# Rule to build all files generated by this target.
CMakeFiles/RunSetup.dir/build: RunSetup

.PHONY : CMakeFiles/RunSetup.dir/build

CMakeFiles/RunSetup.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RunSetup.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RunSetup.dir/clean

CMakeFiles/RunSetup.dir/depend:
	cd /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/Linux-CentOS_7-gcc_4.8-x86_64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/cmake /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/cmake /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/Linux-CentOS_7-gcc_4.8-x86_64 /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/Linux-CentOS_7-gcc_4.8-x86_64 /home/t2k/aspeers/Highland_Installs/HighLAND_2.89/highlandEventModel_2.43/Linux-CentOS_7-gcc_4.8-x86_64/CMakeFiles/RunSetup.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RunSetup.dir/depend
