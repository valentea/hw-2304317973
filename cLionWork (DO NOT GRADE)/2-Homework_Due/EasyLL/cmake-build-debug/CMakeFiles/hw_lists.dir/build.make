# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /cygdrive/c/Users/Alex/.CLion2016.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Alex/.CLion2016.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/hw_lists.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw_lists.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw_lists.dir/flags.make

CMakeFiles/hw_lists.dir/hw2_LL.cpp.o: CMakeFiles/hw_lists.dir/flags.make
CMakeFiles/hw_lists.dir/hw2_LL.cpp.o: ../hw2_LL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw_lists.dir/hw2_LL.cpp.o"
	/usr/bin/c++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw_lists.dir/hw2_LL.cpp.o -c "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/hw2_LL.cpp"

CMakeFiles/hw_lists.dir/hw2_LL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw_lists.dir/hw2_LL.cpp.i"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/hw2_LL.cpp" > CMakeFiles/hw_lists.dir/hw2_LL.cpp.i

CMakeFiles/hw_lists.dir/hw2_LL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw_lists.dir/hw2_LL.cpp.s"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/hw2_LL.cpp" -o CMakeFiles/hw_lists.dir/hw2_LL.cpp.s

CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.requires:

.PHONY : CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.requires

CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.provides: CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.requires
	$(MAKE) -f CMakeFiles/hw_lists.dir/build.make CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.provides.build
.PHONY : CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.provides

CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.provides.build: CMakeFiles/hw_lists.dir/hw2_LL.cpp.o


# Object files for target hw_lists
hw_lists_OBJECTS = \
"CMakeFiles/hw_lists.dir/hw2_LL.cpp.o"

# External object files for target hw_lists
hw_lists_EXTERNAL_OBJECTS =

hw_lists.exe: CMakeFiles/hw_lists.dir/hw2_LL.cpp.o
hw_lists.exe: CMakeFiles/hw_lists.dir/build.make
hw_lists.exe: CMakeFiles/hw_lists.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw_lists.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw_lists.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw_lists.dir/build: hw_lists.exe

.PHONY : CMakeFiles/hw_lists.dir/build

CMakeFiles/hw_lists.dir/requires: CMakeFiles/hw_lists.dir/hw2_LL.cpp.o.requires

.PHONY : CMakeFiles/hw_lists.dir/requires

CMakeFiles/hw_lists.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw_lists.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw_lists.dir/clean

CMakeFiles/hw_lists.dir/depend:
	cd "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL" "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL" "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/cmake-build-debug" "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/cmake-build-debug" "/cygdrive/c/Users/Alex/Documents/School/College/2017.1 Spring/CSCI 104/Homework/hw-2304317973/cLionWork (DO NOT GRADE)/2-Homework_Due/EasyLL/cmake-build-debug/CMakeFiles/hw_lists.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/hw_lists.dir/depend

