# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/apps/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /opt/apps/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home1/07320/whick002/enzo-e_inference

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home1/07320/whick002/enzo-e_inference/build_dev

# Include any dependencies generated for this target.
include src/Cello/CMakeFiles/tester_default.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Cello/CMakeFiles/tester_default.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Cello/CMakeFiles/tester_default.dir/progress.make

# Include the compile flags for this target's objects.
include src/Cello/CMakeFiles/tester_default.dir/flags.make

src/Cello/CMakeFiles/tester_default.dir/main.cpp.o: src/Cello/CMakeFiles/tester_default.dir/flags.make
src/Cello/CMakeFiles/tester_default.dir/main.cpp.o: /home1/07320/whick002/enzo-e_inference/src/Cello/main.cpp
src/Cello/CMakeFiles/tester_default.dir/main.cpp.o: src/Cello/CMakeFiles/tester_default.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home1/07320/whick002/enzo-e_inference/build_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Cello/CMakeFiles/tester_default.dir/main.cpp.o"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && /opt/intel/compilers_and_libraries_2020.1.217/linux/bin/intel64/icpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Cello/CMakeFiles/tester_default.dir/main.cpp.o -MF CMakeFiles/tester_default.dir/main.cpp.o.d -o CMakeFiles/tester_default.dir/main.cpp.o -c /home1/07320/whick002/enzo-e_inference/src/Cello/main.cpp

src/Cello/CMakeFiles/tester_default.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tester_default.dir/main.cpp.i"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && /opt/intel/compilers_and_libraries_2020.1.217/linux/bin/intel64/icpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home1/07320/whick002/enzo-e_inference/src/Cello/main.cpp > CMakeFiles/tester_default.dir/main.cpp.i

src/Cello/CMakeFiles/tester_default.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tester_default.dir/main.cpp.s"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && /opt/intel/compilers_and_libraries_2020.1.217/linux/bin/intel64/icpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home1/07320/whick002/enzo-e_inference/src/Cello/main.cpp -o CMakeFiles/tester_default.dir/main.cpp.s

# Object files for target tester_default
tester_default_OBJECTS = \
"CMakeFiles/tester_default.dir/main.cpp.o"

# External object files for target tester_default
tester_default_EXTERNAL_OBJECTS =

src/Cello/libtester_default.a: src/Cello/CMakeFiles/tester_default.dir/main.cpp.o
src/Cello/libtester_default.a: src/Cello/CMakeFiles/tester_default.dir/build.make
src/Cello/libtester_default.a: src/Cello/CMakeFiles/tester_default.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home1/07320/whick002/enzo-e_inference/build_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtester_default.a"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && $(CMAKE_COMMAND) -P CMakeFiles/tester_default.dir/cmake_clean_target.cmake
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tester_default.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Cello/CMakeFiles/tester_default.dir/build: src/Cello/libtester_default.a
.PHONY : src/Cello/CMakeFiles/tester_default.dir/build

src/Cello/CMakeFiles/tester_default.dir/clean:
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && $(CMAKE_COMMAND) -P CMakeFiles/tester_default.dir/cmake_clean.cmake
.PHONY : src/Cello/CMakeFiles/tester_default.dir/clean

src/Cello/CMakeFiles/tester_default.dir/depend:
	cd /home1/07320/whick002/enzo-e_inference/build_dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home1/07320/whick002/enzo-e_inference /home1/07320/whick002/enzo-e_inference/src/Cello /home1/07320/whick002/enzo-e_inference/build_dev /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello/CMakeFiles/tester_default.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Cello/CMakeFiles/tester_default.dir/depend

