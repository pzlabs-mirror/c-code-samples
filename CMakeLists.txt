# At least CMake v3.21 is needed because of C17 support
cmake_minimum_required(VERSION 3.21)

project(c_examples
	DESCRIPTION "A set of simple example programs in C"
	LANGUAGES C
)

# Tell the compiler to run in C17 mode (ISO/IEC 9899:2018). Turn the compiler extensions off
# (e.g. it forces -std=c17 instead of -std=gnu17 on gcc and clang)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS FALSE)

# Use folders for nice tree in Visual Studio and XCode
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

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

# Define executables with the actual example code

add_executable(hello_world hello_world/hello_world.c)

add_executable(swap_vars_a swap_vars/swap_a.c)
add_executable(swap_vars_b swap_vars/swap_b.c)
add_executable(swap_vars_c swap_vars/swap_c.c)

add_executable(lab1_1 lab1/lab1_1.c)
add_executable(lab1_2 lab1/lab1_2.c)
target_link_libraries(lab1_1 PRIVATE stdlib::math)

# Install every executable into default install prefix. To run installation step,
# execute `cmake --build ${YOUR_BUILD_DIRECTORY} --target install`
install(
	TARGETS
		hello_world
		lab1_1
		lab1_2
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

