# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/kat/Documentos/CSUNSA7/8voSemestre/ComputacionGrafica/GRAFICA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kat/Documentos/CSUNSA7/8voSemestre/ComputacionGrafica/GRAFICA

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kat/Documentos/CSUNSA7/8voSemestre/ComputacionGrafica/GRAFICA/CMakeFiles /home/kat/Documentos/CSUNSA7/8voSemestre/ComputacionGrafica/GRAFICA/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/kat/Documentos/CSUNSA7/8voSemestre/ComputacionGrafica/GRAFICA/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named greedy_projection

# Build rule for target.
greedy_projection: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 greedy_projection
.PHONY : greedy_projection

# fast build rule for target.
greedy_projection/fast:
	$(MAKE) -f CMakeFiles/greedy_projection.dir/build.make CMakeFiles/greedy_projection.dir/build
.PHONY : greedy_projection/fast

greedy_projection.o: greedy_projection.cpp.o

.PHONY : greedy_projection.o

# target to build an object file
greedy_projection.cpp.o:
	$(MAKE) -f CMakeFiles/greedy_projection.dir/build.make CMakeFiles/greedy_projection.dir/greedy_projection.cpp.o
.PHONY : greedy_projection.cpp.o

greedy_projection.i: greedy_projection.cpp.i

.PHONY : greedy_projection.i

# target to preprocess a source file
greedy_projection.cpp.i:
	$(MAKE) -f CMakeFiles/greedy_projection.dir/build.make CMakeFiles/greedy_projection.dir/greedy_projection.cpp.i
.PHONY : greedy_projection.cpp.i

greedy_projection.s: greedy_projection.cpp.s

.PHONY : greedy_projection.s

# target to generate assembly for a file
greedy_projection.cpp.s:
	$(MAKE) -f CMakeFiles/greedy_projection.dir/build.make CMakeFiles/greedy_projection.dir/greedy_projection.cpp.s
.PHONY : greedy_projection.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... greedy_projection"
	@echo "... greedy_projection.o"
	@echo "... greedy_projection.i"
	@echo "... greedy_projection.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

