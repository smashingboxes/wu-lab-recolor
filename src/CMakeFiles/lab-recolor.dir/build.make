# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joe/src/wu-lab-recolor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joe/src/wu-lab-recolor

# Include any dependencies generated for this target.
include src/CMakeFiles/lab-recolor.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/lab-recolor.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/lab-recolor.dir/flags.make

src/CMakeFiles/lab-recolor.dir/main.c.o: src/CMakeFiles/lab-recolor.dir/flags.make
src/CMakeFiles/lab-recolor.dir/main.c.o: src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/joe/src/wu-lab-recolor/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/lab-recolor.dir/main.c.o"
	cd /home/joe/src/wu-lab-recolor/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/lab-recolor.dir/main.c.o   -c /home/joe/src/wu-lab-recolor/src/main.c

src/CMakeFiles/lab-recolor.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab-recolor.dir/main.c.i"
	cd /home/joe/src/wu-lab-recolor/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/joe/src/wu-lab-recolor/src/main.c > CMakeFiles/lab-recolor.dir/main.c.i

src/CMakeFiles/lab-recolor.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab-recolor.dir/main.c.s"
	cd /home/joe/src/wu-lab-recolor/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/joe/src/wu-lab-recolor/src/main.c -o CMakeFiles/lab-recolor.dir/main.c.s

src/CMakeFiles/lab-recolor.dir/main.c.o.requires:
.PHONY : src/CMakeFiles/lab-recolor.dir/main.c.o.requires

src/CMakeFiles/lab-recolor.dir/main.c.o.provides: src/CMakeFiles/lab-recolor.dir/main.c.o.requires
	$(MAKE) -f src/CMakeFiles/lab-recolor.dir/build.make src/CMakeFiles/lab-recolor.dir/main.c.o.provides.build
.PHONY : src/CMakeFiles/lab-recolor.dir/main.c.o.provides

src/CMakeFiles/lab-recolor.dir/main.c.o.provides.build: src/CMakeFiles/lab-recolor.dir/main.c.o

# Object files for target lab-recolor
lab__recolor_OBJECTS = \
"CMakeFiles/lab-recolor.dir/main.c.o"

# External object files for target lab-recolor
lab__recolor_EXTERNAL_OBJECTS =

src/lab-recolor: src/CMakeFiles/lab-recolor.dir/main.c.o
src/lab-recolor: src/CMakeFiles/lab-recolor.dir/build.make
src/lab-recolor: build/libLabRecolor.a
src/lab-recolor: /usr/lib/x86_64-linux-gnu/libMagickWand.so
src/lab-recolor: src/CMakeFiles/lab-recolor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable lab-recolor"
	cd /home/joe/src/wu-lab-recolor/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab-recolor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/lab-recolor.dir/build: src/lab-recolor
.PHONY : src/CMakeFiles/lab-recolor.dir/build

src/CMakeFiles/lab-recolor.dir/requires: src/CMakeFiles/lab-recolor.dir/main.c.o.requires
.PHONY : src/CMakeFiles/lab-recolor.dir/requires

src/CMakeFiles/lab-recolor.dir/clean:
	cd /home/joe/src/wu-lab-recolor/src && $(CMAKE_COMMAND) -P CMakeFiles/lab-recolor.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/lab-recolor.dir/clean

src/CMakeFiles/lab-recolor.dir/depend:
	cd /home/joe/src/wu-lab-recolor && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joe/src/wu-lab-recolor /home/joe/src/wu-lab-recolor/src /home/joe/src/wu-lab-recolor /home/joe/src/wu-lab-recolor/src /home/joe/src/wu-lab-recolor/src/CMakeFiles/lab-recolor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/lab-recolor.dir/depend

