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
CMAKE_SOURCE_DIR = /home/iramalin/cpp_orderbook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/iramalin/cpp_orderbook/build

# Include any dependencies generated for this target.
include CMakeFiles/order_book.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/order_book.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/order_book.dir/flags.make

CMakeFiles/order_book.dir/src/main.cpp.o: CMakeFiles/order_book.dir/flags.make
CMakeFiles/order_book.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/iramalin/cpp_orderbook/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/order_book.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/order_book.dir/src/main.cpp.o -c /home/iramalin/cpp_orderbook/src/main.cpp

CMakeFiles/order_book.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/order_book.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/iramalin/cpp_orderbook/src/main.cpp > CMakeFiles/order_book.dir/src/main.cpp.i

CMakeFiles/order_book.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/order_book.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/iramalin/cpp_orderbook/src/main.cpp -o CMakeFiles/order_book.dir/src/main.cpp.s

CMakeFiles/order_book.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/order_book.dir/src/main.cpp.o.requires

CMakeFiles/order_book.dir/src/main.cpp.o.provides: CMakeFiles/order_book.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/order_book.dir/build.make CMakeFiles/order_book.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/order_book.dir/src/main.cpp.o.provides

CMakeFiles/order_book.dir/src/main.cpp.o.provides.build: CMakeFiles/order_book.dir/src/main.cpp.o


CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o: CMakeFiles/order_book.dir/flags.make
CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o: ../src/OrderInputManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/iramalin/cpp_orderbook/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o -c /home/iramalin/cpp_orderbook/src/OrderInputManager.cpp

CMakeFiles/order_book.dir/src/OrderInputManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/order_book.dir/src/OrderInputManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/iramalin/cpp_orderbook/src/OrderInputManager.cpp > CMakeFiles/order_book.dir/src/OrderInputManager.cpp.i

CMakeFiles/order_book.dir/src/OrderInputManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/order_book.dir/src/OrderInputManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/iramalin/cpp_orderbook/src/OrderInputManager.cpp -o CMakeFiles/order_book.dir/src/OrderInputManager.cpp.s

CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.requires:

.PHONY : CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.requires

CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.provides: CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/order_book.dir/build.make CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.provides.build
.PHONY : CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.provides

CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.provides.build: CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o


CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o: CMakeFiles/order_book.dir/flags.make
CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o: ../src/LimitOrderMatcher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/iramalin/cpp_orderbook/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o -c /home/iramalin/cpp_orderbook/src/LimitOrderMatcher.cpp

CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/iramalin/cpp_orderbook/src/LimitOrderMatcher.cpp > CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.i

CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/iramalin/cpp_orderbook/src/LimitOrderMatcher.cpp -o CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.s

CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.requires:

.PHONY : CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.requires

CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.provides: CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.requires
	$(MAKE) -f CMakeFiles/order_book.dir/build.make CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.provides.build
.PHONY : CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.provides

CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.provides.build: CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o


# Object files for target order_book
order_book_OBJECTS = \
"CMakeFiles/order_book.dir/src/main.cpp.o" \
"CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o" \
"CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o"

# External object files for target order_book
order_book_EXTERNAL_OBJECTS =

order_book: CMakeFiles/order_book.dir/src/main.cpp.o
order_book: CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o
order_book: CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o
order_book: CMakeFiles/order_book.dir/build.make
order_book: CMakeFiles/order_book.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/iramalin/cpp_orderbook/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable order_book"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/order_book.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/order_book.dir/build: order_book

.PHONY : CMakeFiles/order_book.dir/build

CMakeFiles/order_book.dir/requires: CMakeFiles/order_book.dir/src/main.cpp.o.requires
CMakeFiles/order_book.dir/requires: CMakeFiles/order_book.dir/src/OrderInputManager.cpp.o.requires
CMakeFiles/order_book.dir/requires: CMakeFiles/order_book.dir/src/LimitOrderMatcher.cpp.o.requires

.PHONY : CMakeFiles/order_book.dir/requires

CMakeFiles/order_book.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/order_book.dir/cmake_clean.cmake
.PHONY : CMakeFiles/order_book.dir/clean

CMakeFiles/order_book.dir/depend:
	cd /home/iramalin/cpp_orderbook/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/iramalin/cpp_orderbook /home/iramalin/cpp_orderbook /home/iramalin/cpp_orderbook/build /home/iramalin/cpp_orderbook/build /home/iramalin/cpp_orderbook/build/CMakeFiles/order_book.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/order_book.dir/depend

