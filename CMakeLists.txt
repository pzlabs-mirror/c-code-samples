cmake_minimum_required(VERSION 3.21) # At least CMake v3.21 is needed because of C17 support

project(c_code_samples
	DESCRIPTION "A collection of code samples and examples for projects in C"
	LANGUAGES C
)

# Tell the compiler to run in C17 mode (ISO/IEC 9899:2018). Turn the compiler extensions off
# (i.e. it forces -std=c17 instead of -std=gnu17 on gcc and clang)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS FALSE)

# Use folders for nice tree in Visual Studio and XCode
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

# Generate compile_commands.json which is a format widely accepted by third-party tools
# (code formatters, static analyzers, linters, project viewers, LSP servers, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Change the default install prefix to project_dir/install
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
	AND "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}"
)
	set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "Install root path" FORCE)
	message(STATUS "Install prefix has been set to '${CMAKE_INSTALL_PREFIX}'")
endif()

# Under Linux, the mathematical functions from <math.h> are defined in a separate library libm.
# Link to this target if you use <math.h>

add_library(stdlib_math INTERFACE)
add_library(stdlib::math ALIAS stdlib_math)

if(UNIX)
	target_link_libraries(stdlib_math INTERFACE m)
endif()

# Enable targets for *default* compilation flags
include(cmake/CompilerFlags.cmake)

# Define a single target with unified compiler flags
add_library(flags INTERFACE)
add_library(flags::flags ALIAS flags)

target_link_libraries(flags INTERFACE
	cflags::default_warnings
	cflags::default_errors
	cflags::default_compile_options
)

# Define executables with the actual example code

add_executable(hello_world src/hello_world/hello_world.c)
target_link_libraries(hello_world PRIVATE flags::flags)

add_executable(swap_vars_a src/swap_vars/swap_a.c)
target_link_libraries(swap_vars_a PRIVATE flags::flags)

add_executable(swap_vars_b src/swap_vars/swap_b.c)
target_link_libraries(swap_vars_b PRIVATE flags::flags)

add_executable(swap_vars_c src/swap_vars/swap_c.c)
target_link_libraries(swap_vars_c PRIVATE flags::flags)

add_executable(lab1_1 src/lab1/lab1_1.c)
target_link_libraries(lab1_1 PRIVATE flags::flags stdlib::math)

add_executable(lab1_2 src/lab1/lab1_2.c)
target_link_libraries(lab1_2 PRIVATE flags::flags)

# Install every executable into default install prefix. To run installation step,
# execute `cmake --build ${YOUR_BUILD_DIRECTORY} --target install`
install(
	TARGETS
		hello_world
		swap_vars_a
		swap_vars_b
		swap_vars_c
		lab1_1
		lab1_2
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
