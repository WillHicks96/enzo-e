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
include src/Cello/CMakeFiles/test_view_collec.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/Cello/CMakeFiles/test_view_collec.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Cello/CMakeFiles/test_view_collec.dir/progress.make

# Include the compile flags for this target's objects.
include src/Cello/CMakeFiles/test_view_collec.dir/flags.make

src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o: src/Cello/CMakeFiles/test_view_collec.dir/flags.make
src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o: /home1/07320/whick002/enzo-e_inference/src/Cello/test_ViewCollec.cpp
src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o: src/Cello/CMakeFiles/test_view_collec.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home1/07320/whick002/enzo-e_inference/build_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && /opt/intel/compilers_and_libraries_2020.1.217/linux/bin/intel64/icpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o -MF CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o.d -o CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o -c /home1/07320/whick002/enzo-e_inference/src/Cello/test_ViewCollec.cpp

src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.i"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && /opt/intel/compilers_and_libraries_2020.1.217/linux/bin/intel64/icpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home1/07320/whick002/enzo-e_inference/src/Cello/test_ViewCollec.cpp > CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.i

src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.s"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && /opt/intel/compilers_and_libraries_2020.1.217/linux/bin/intel64/icpc $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home1/07320/whick002/enzo-e_inference/src/Cello/test_ViewCollec.cpp -o CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.s

# Object files for target test_view_collec
test_view_collec_OBJECTS = \
"CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o"

# External object files for target test_view_collec
test_view_collec_EXTERNAL_OBJECTS =

bin/test_view_collec: src/Cello/CMakeFiles/test_view_collec.dir/test_ViewCollec.cpp.o
bin/test_view_collec: src/Cello/CMakeFiles/test_view_collec.dir/build.make
bin/test_view_collec: src/Cello/libtester_default.a
bin/test_view_collec: src/Cello/libtest_Unit.a
bin/test_view_collec: src/Cello/liberror.a
bin/test_view_collec: src/Cello/libmonitor.a
bin/test_view_collec: src/Cello/libcello_component.a
bin/test_view_collec: src/Cello/libperformance.a
bin/test_view_collec: src/Cello/libcharm_component.a
bin/test_view_collec: src/Cello/libsimulation.a
bin/test_view_collec: src/Cello/libparameters.a
bin/test_view_collec: src/Cello/libmemory.a
bin/test_view_collec: src/Cello/libmesh.a
bin/test_view_collec: src/Cello/libdisk.a
bin/test_view_collec: src/Cello/libproblem.a
bin/test_view_collec: src/Cello/libdata.a
bin/test_view_collec: src/Cello/libio.a
bin/test_view_collec: src/Cello/libcompute.a
bin/test_view_collec: src/Cello/libcontrol.a
bin/test_view_collec: src/Cello/liberror.a
bin/test_view_collec: src/Cello/libmonitor.a
bin/test_view_collec: src/Cello/libcello_component.a
bin/test_view_collec: src/Cello/libperformance.a
bin/test_view_collec: src/Cello/libcharm_component.a
bin/test_view_collec: src/Cello/libsimulation.a
bin/test_view_collec: src/Cello/libparameters.a
bin/test_view_collec: src/Cello/libmemory.a
bin/test_view_collec: src/Cello/libmesh.a
bin/test_view_collec: src/Cello/libdisk.a
bin/test_view_collec: src/Cello/libproblem.a
bin/test_view_collec: src/Cello/libdata.a
bin/test_view_collec: src/Cello/libio.a
bin/test_view_collec: src/Cello/libcompute.a
bin/test_view_collec: src/Cello/libcontrol.a
bin/test_view_collec: /opt/apps/intel19/hdf5/1.10.4/x86_64/lib/libhdf5.so
bin/test_view_collec: /opt/apps/intel19/hdf5/1.10.4/x86_64/lib/libsz.so
bin/test_view_collec: /usr/lib64/libz.so
bin/test_view_collec: /opt/apps/intel19/hdf5/1.10.4/x86_64/lib/libsz.so
bin/test_view_collec: /usr/lib64/libz.so
bin/test_view_collec: /usr/lib64/libdl.so
bin/test_view_collec: /usr/lib64/libm.so
bin/test_view_collec: /opt/apps/intel19/python3_7/boost/1.72/lib/libboost_filesystem.so.1.72.0
bin/test_view_collec: src/External/libpngwriter.so
bin/test_view_collec: /usr/lib64/libpng.so
bin/test_view_collec: /usr/lib64/libz.so
bin/test_view_collec: src/Cello/CMakeFiles/test_view_collec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home1/07320/whick002/enzo-e_inference/build_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/test_view_collec"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_view_collec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Cello/CMakeFiles/test_view_collec.dir/build: bin/test_view_collec
.PHONY : src/Cello/CMakeFiles/test_view_collec.dir/build

src/Cello/CMakeFiles/test_view_collec.dir/clean:
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && $(CMAKE_COMMAND) -P CMakeFiles/test_view_collec.dir/cmake_clean.cmake
.PHONY : src/Cello/CMakeFiles/test_view_collec.dir/clean

src/Cello/CMakeFiles/test_view_collec.dir/depend:
	cd /home1/07320/whick002/enzo-e_inference/build_dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home1/07320/whick002/enzo-e_inference /home1/07320/whick002/enzo-e_inference/src/Cello /home1/07320/whick002/enzo-e_inference/build_dev /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello/CMakeFiles/test_view_collec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Cello/CMakeFiles/test_view_collec.dir/depend

