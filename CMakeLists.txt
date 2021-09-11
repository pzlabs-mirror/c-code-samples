cmake_minimum_required(VERSION 3.21)

project(c_examples
	DESCRIPTION "A set of simple example programs in C"
	LANGUAGES C
)

# Tell the compiler to run in C17 mode (ISO/IEC 9899:2018). Turn extensions off (e.g. use -std=c17
# instead of -std=gnu17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_C_EXTENSIONS FALSE)

# Use folders for nice tree in Visual Studio and XCode
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)

# Change default install prefix to project_dir/install
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
	AND "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}"
)
	set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE PATH "Install root path" FORCE)
	message(STATUS "Install prefix has been set to '${CMAKE_INSTALL_PREFIX}'")
endif()

add_executable(hello_world src/hello_world.c)

install(
	TARGETS
		hello_world
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

