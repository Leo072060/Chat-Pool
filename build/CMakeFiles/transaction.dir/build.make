# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/twh/TinyBridge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/twh/TinyBridge/build

# Include any dependencies generated for this target.
include CMakeFiles/transaction.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/transaction.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/transaction.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/transaction.dir/flags.make

CMakeFiles/transaction.dir/src/message/message.cpp.o: CMakeFiles/transaction.dir/flags.make
CMakeFiles/transaction.dir/src/message/message.cpp.o: /home/twh/TinyBridge/src/message/message.cpp
CMakeFiles/transaction.dir/src/message/message.cpp.o: CMakeFiles/transaction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/twh/TinyBridge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/transaction.dir/src/message/message.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/transaction.dir/src/message/message.cpp.o -MF CMakeFiles/transaction.dir/src/message/message.cpp.o.d -o CMakeFiles/transaction.dir/src/message/message.cpp.o -c /home/twh/TinyBridge/src/message/message.cpp

CMakeFiles/transaction.dir/src/message/message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/transaction.dir/src/message/message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/twh/TinyBridge/src/message/message.cpp > CMakeFiles/transaction.dir/src/message/message.cpp.i

CMakeFiles/transaction.dir/src/message/message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/transaction.dir/src/message/message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/twh/TinyBridge/src/message/message.cpp -o CMakeFiles/transaction.dir/src/message/message.cpp.s

CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o: CMakeFiles/transaction.dir/flags.make
CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o: /home/twh/TinyBridge/src/transaction/chatPool/chatPool.cpp
CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o: CMakeFiles/transaction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/twh/TinyBridge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o -MF CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o.d -o CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o -c /home/twh/TinyBridge/src/transaction/chatPool/chatPool.cpp

CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/twh/TinyBridge/src/transaction/chatPool/chatPool.cpp > CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.i

CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/twh/TinyBridge/src/transaction/chatPool/chatPool.cpp -o CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.s

CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o: CMakeFiles/transaction.dir/flags.make
CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o: /home/twh/TinyBridge/src/transaction/transaction.cpp
CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o: CMakeFiles/transaction.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/twh/TinyBridge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o -MF CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o.d -o CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o -c /home/twh/TinyBridge/src/transaction/transaction.cpp

CMakeFiles/transaction.dir/src/transaction/transaction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/transaction.dir/src/transaction/transaction.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/twh/TinyBridge/src/transaction/transaction.cpp > CMakeFiles/transaction.dir/src/transaction/transaction.cpp.i

CMakeFiles/transaction.dir/src/transaction/transaction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/transaction.dir/src/transaction/transaction.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/twh/TinyBridge/src/transaction/transaction.cpp -o CMakeFiles/transaction.dir/src/transaction/transaction.cpp.s

# Object files for target transaction
transaction_OBJECTS = \
"CMakeFiles/transaction.dir/src/message/message.cpp.o" \
"CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o" \
"CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o"

# External object files for target transaction
transaction_EXTERNAL_OBJECTS =

transaction: CMakeFiles/transaction.dir/src/message/message.cpp.o
transaction: CMakeFiles/transaction.dir/src/transaction/chatPool/chatPool.cpp.o
transaction: CMakeFiles/transaction.dir/src/transaction/transaction.cpp.o
transaction: CMakeFiles/transaction.dir/build.make
transaction: CMakeFiles/transaction.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/twh/TinyBridge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable transaction"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/transaction.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/transaction.dir/build: transaction
.PHONY : CMakeFiles/transaction.dir/build

CMakeFiles/transaction.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/transaction.dir/cmake_clean.cmake
.PHONY : CMakeFiles/transaction.dir/clean

CMakeFiles/transaction.dir/depend:
	cd /home/twh/TinyBridge/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/twh/TinyBridge /home/twh/TinyBridge /home/twh/TinyBridge/build /home/twh/TinyBridge/build /home/twh/TinyBridge/build/CMakeFiles/transaction.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/transaction.dir/depend

