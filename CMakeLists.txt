cmake_minimum_required(VERSION 3.21) # At least CMake v3.21 is needed because of C17 support

project(c_code_samples
	DESCRIPTION "A collection of code samples and examples for projects in C"
	LANGUAGES C
)

option(C_CODE_SAMPLES_WITH_EXTRAS "Build extra targets" OFF)

# Tell the compiler to run in C17 mode (ISO/IEC 9899:2018).
set(CMAKE_C_STANDARD 17)
# This should be set to TRUE to fail if the compiler doesn't support C17
set(CMAKE_C_STANDARD_REQUIRED FALSE)
# Turn the compiler extensions off (i.e. it forces -std=c17 instead of -std=gnu17 on gcc and clang)
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
# You can link to this target if you use <math.h>

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
target_include_directories(flags INTERFACE src)

# Define executables with the actual example code

add_executable(hello_world src/hello_world/hello_world.c)
target_link_libraries(hello_world PRIVATE flags::flags)

add_executable(swap_vars_a src/swap_vars/swap_a.c)
target_link_libraries(swap_vars_a PRIVATE flags::flags)

add_executable(swap_vars_b src/swap_vars/swap_b.c)
target_link_libraries(swap_vars_b PRIVATE flags::flags)

add_executable(swap_vars_c src/swap_vars/swap_c.c)
target_link_libraries(swap_vars_c PRIVATE flags::flags)

add_executable(fizzbuzz_naive src/fizzbuzz/fizzbuzz_naive.c)
target_link_libraries(fizzbuzz_naive PRIVATE flags::flags)

add_executable(fizzbuzz_naive_vars src/fizzbuzz/fizzbuzz_naive_vars.c)
target_link_libraries(fizzbuzz_naive_vars PRIVATE flags::flags)

add_executable(fizzbuzz_with_flag src/fizzbuzz/fizzbuzz_with_flag.c)
target_link_libraries(fizzbuzz_with_flag PRIVATE flags::flags)

add_executable(fizzbuzz_bitmask_switch src/fizzbuzz/fizzbuzz_bitmask_switch.c)
target_link_libraries(fizzbuzz_bitmask_switch PRIVATE flags::flags)

add_executable(fizzbuzz_counters src/fizzbuzz/fizzbuzz_counters.c)
target_link_libraries(fizzbuzz_counters PRIVATE flags::flags)

add_executable(fizzbuzz_two_branches src/fizzbuzz/fizzbuzz_two_branches.c)
target_link_libraries(fizzbuzz_two_branches PRIVATE flags::flags)

add_executable(ascii_canvas src/canvas/ascii_canvas.c)
target_link_libraries(ascii_canvas PRIVATE flags::flags stdlib::math)

add_executable(array_search
	src/search/search_common.h
	src/search/linear_search.h
	src/search/linear_search.c
	src/search/binary_search.h
	src/search/binary_search.c
	src/search/test_array_search.c
)
target_link_libraries(array_search PRIVATE flags::flags)

add_executable(variadic_fold src/variadic_fold/variadic_fold.c)
target_link_libraries(variadic_fold PRIVATE flags::flags)

add_executable(strview src/strview/strview.h src/strview/strview.c src/strview/test_strview.c)
target_link_libraries(strview PRIVATE flags::flags)

add_executable(lab1_1 src/lab1/lab1_1.c)
target_link_libraries(lab1_1 PRIVATE flags::flags stdlib::math)

add_executable(lab1_2 src/lab1/lab1_2.c)
target_link_libraries(lab1_2 PRIVATE flags::flags)

add_executable(lab2_2 src/lab2/lab2_2.c)
target_link_libraries(lab2_2 PRIVATE flags::flags stdlib::math)

add_executable(lab3_2 src/lab3/lab3_2.c)
target_link_libraries(lab3_2 PRIVATE flags::flags)

add_executable(lab4_2 src/lab4/lab4_2.c)
target_link_libraries(lab4_2 PRIVATE flags::flags)

# Install every executable into default install prefix. To run installation step, one should
# execute `cmake --build ${YOUR_BUILD_DIRECTORY} --target install`
install(
	TARGETS
		hello_world
		swap_vars_a
		swap_vars_b
		swap_vars_c
		fizzbuzz_naive
		fizzbuzz_naive_vars
		fizzbuzz_with_flag
		fizzbuzz_bitmask_switch
		fizzbuzz_counters
		fizzbuzz_two_branches
		ascii_canvas
		array_search
		variadic_fold
		strview
		lab1_1
		lab1_2
		lab2_2
		lab3_2
		lab4_2
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

# Extras

if(C_CODE_SAMPLES_WITH_EXTRAS)
	add_executable(test1 src/extra/test1/test1.c)
	target_link_libraries(test1 PRIVATE flags::flags)

	install(
		TARGETS
			test1
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	)
endif()
