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
CMAKE_SOURCE_DIR = /home/elpoublo/Projects/hell_and_heaven

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/elpoublo/Projects/hell_and_heaven

# Include any dependencies generated for this target.
include hh_exceptions/CMakeFiles/hh_exception.dir/depend.make

# Include the progress variables for this target.
include hh_exceptions/CMakeFiles/hh_exception.dir/progress.make

# Include the compile flags for this target's objects.
include hh_exceptions/CMakeFiles/hh_exception.dir/flags.make

hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o: hh_exceptions/CMakeFiles/hh_exception.dir/flags.make
hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o: hh_exceptions/hh_exceptions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/elpoublo/Projects/hell_and_heaven/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o"
	cd /home/elpoublo/Projects/hell_and_heaven/hh_exceptions && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o -c /home/elpoublo/Projects/hell_and_heaven/hh_exceptions/hh_exceptions.cpp

hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hh_exception.dir/hh_exceptions.cpp.i"
	cd /home/elpoublo/Projects/hell_and_heaven/hh_exceptions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/elpoublo/Projects/hell_and_heaven/hh_exceptions/hh_exceptions.cpp > CMakeFiles/hh_exception.dir/hh_exceptions.cpp.i

hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hh_exception.dir/hh_exceptions.cpp.s"
	cd /home/elpoublo/Projects/hell_and_heaven/hh_exceptions && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/elpoublo/Projects/hell_and_heaven/hh_exceptions/hh_exceptions.cpp -o CMakeFiles/hh_exception.dir/hh_exceptions.cpp.s

hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.requires:

.PHONY : hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.requires

hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.provides: hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.requires
	$(MAKE) -f hh_exceptions/CMakeFiles/hh_exception.dir/build.make hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.provides.build
.PHONY : hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.provides

hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.provides.build: hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o


# Object files for target hh_exception
hh_exception_OBJECTS = \
"CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o"

# External object files for target hh_exception
hh_exception_EXTERNAL_OBJECTS =

hh_exceptions/libhh_exception.a: hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o
hh_exceptions/libhh_exception.a: hh_exceptions/CMakeFiles/hh_exception.dir/build.make
hh_exceptions/libhh_exception.a: hh_exceptions/CMakeFiles/hh_exception.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/elpoublo/Projects/hell_and_heaven/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libhh_exception.a"
	cd /home/elpoublo/Projects/hell_and_heaven/hh_exceptions && $(CMAKE_COMMAND) -P CMakeFiles/hh_exception.dir/cmake_clean_target.cmake
	cd /home/elpoublo/Projects/hell_and_heaven/hh_exceptions && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hh_exception.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hh_exceptions/CMakeFiles/hh_exception.dir/build: hh_exceptions/libhh_exception.a

.PHONY : hh_exceptions/CMakeFiles/hh_exception.dir/build

hh_exceptions/CMakeFiles/hh_exception.dir/requires: hh_exceptions/CMakeFiles/hh_exception.dir/hh_exceptions.cpp.o.requires

.PHONY : hh_exceptions/CMakeFiles/hh_exception.dir/requires

hh_exceptions/CMakeFiles/hh_exception.dir/clean:
	cd /home/elpoublo/Projects/hell_and_heaven/hh_exceptions && $(CMAKE_COMMAND) -P CMakeFiles/hh_exception.dir/cmake_clean.cmake
.PHONY : hh_exceptions/CMakeFiles/hh_exception.dir/clean

hh_exceptions/CMakeFiles/hh_exception.dir/depend:
	cd /home/elpoublo/Projects/hell_and_heaven && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/elpoublo/Projects/hell_and_heaven /home/elpoublo/Projects/hell_and_heaven/hh_exceptions /home/elpoublo/Projects/hell_and_heaven /home/elpoublo/Projects/hell_and_heaven/hh_exceptions /home/elpoublo/Projects/hell_and_heaven/hh_exceptions/CMakeFiles/hh_exception.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hh_exceptions/CMakeFiles/hh_exception.dir/depend

