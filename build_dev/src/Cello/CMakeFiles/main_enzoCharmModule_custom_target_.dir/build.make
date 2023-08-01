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

# Utility rule file for main_enzoCharmModule_custom_target_.

# Include any custom commands dependencies for this target.
include src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/compiler_depend.make

# Include the progress variables for this target.
include src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/progress.make

src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_: src/Cello/main_enzo.decl.h
src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_: src/Cello/main_enzo.def.h

src/Cello/main_enzo.decl.h: /home1/07320/whick002/enzo-e_inference/src/Cello/main_enzo.ci
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home1/07320/whick002/enzo-e_inference/build_dev/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating main_enzo.decl.h, main_enzo.def.h"
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && /home1/07320/whick002/charm/mpi-linux-x86_64-smp-mpicxx/bin/charmc -DCONFIG_USE_GRACKLE\  -DCONFIG_USE_TORCH\  -DBYPASS_CHARM_MEM_LEAK\  /home1/07320/whick002/enzo-e_inference/src/Cello/main_enzo.ci

src/Cello/main_enzo.def.h: src/Cello/main_enzo.decl.h
	@$(CMAKE_COMMAND) -E touch_nocreate src/Cello/main_enzo.def.h

main_enzoCharmModule_custom_target_: src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_
main_enzoCharmModule_custom_target_: src/Cello/main_enzo.decl.h
main_enzoCharmModule_custom_target_: src/Cello/main_enzo.def.h
main_enzoCharmModule_custom_target_: src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/build.make
.PHONY : main_enzoCharmModule_custom_target_

# Rule to build all files generated by this target.
src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/build: main_enzoCharmModule_custom_target_
.PHONY : src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/build

src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/clean:
	cd /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello && $(CMAKE_COMMAND) -P CMakeFiles/main_enzoCharmModule_custom_target_.dir/cmake_clean.cmake
.PHONY : src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/clean

src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/depend:
	cd /home1/07320/whick002/enzo-e_inference/build_dev && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home1/07320/whick002/enzo-e_inference /home1/07320/whick002/enzo-e_inference/src/Cello /home1/07320/whick002/enzo-e_inference/build_dev /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello /home1/07320/whick002/enzo-e_inference/build_dev/src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Cello/CMakeFiles/main_enzoCharmModule_custom_target_.dir/depend

