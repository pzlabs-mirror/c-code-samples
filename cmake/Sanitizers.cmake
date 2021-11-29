add_library(sanitizer_options INTERFACE)
add_library(cflags::sanitizer_options ALIAS sanitizer_options)

set(option_prefix "CFLAGS")
set(option_category "CFLAGS")

if(${CMAKE_CXX_COMPILER_ID})
	set(compiler_id ${CMAKE_CXX_COMPILER_ID})
	set(simulate_id ${CMAKE_CXX_SIMULATE_ID})
else()
	set(compiler_id ${CMAKE_C_COMPILER_ID})
	set(simulate_id ${CMAKE_C_SIMULATE_ID})
endif()

# TODO: MSVC
if(compiler_id STREQUAL "GNU"
		OR (compiler_id MATCHES ".*Clang" AND NOT simulate_id STREQUAL "MSVC"))
	option(${option_prefix}_ENABLE_COVERAGE
		"${option_prefix}: Enable coverage reporting for gcc/clang" OFF)

	if(${option_prefix}_ENABLE_COVERAGE)
		target_compile_options(sanitizer_options INTERFACE --coverage -O0 -g)
		target_link_libraries(sanitizer_options INTERFACE --coverage)
	endif()

	set(sanitizers "")

	option(${option_prefix}_ENABLE_SANITIZER_ADDRESS
		"${option_category}: Enable address sanitizer" OFF)
	if(${option_prefix}_ENABLE_SANITIZER_ADDRESS)
		list(APPEND sanitizers "address")
	endif()

	option(${option_prefix}_ENABLE_SANITIZER_LEAK
		"${option_category}: Enable leak sanitizer" OFF)
	if(${option_prefix}_ENABLE_SANITIZER_LEAK)
		list(APPEND sanitizers "leak")
	endif()

	option(${option_prefix}_ENABLE_SANITIZER_UB
		"${option_category}: Enable undefined behavior sanitizer" OFF)
	if(${option_prefix}_ENABLE_SANITIZER_UB)
		list(APPEND sanitizers "undefined")
	endif()

	option(${option_prefix}_ENABLE_SANITIZER_THREAD
		"${option_category}: Enable thread sanitizer" OFF)
	if(${option_prefix}_ENABLE_SANITIZER_THREAD)
		if("address" IN_LIST sanitizers OR "leak" IN_LIST sanitizers)
			message(WARNING "${option_category}: Thread sanitizer does not work "
				"with address and leak sanitizer enabled")
		else()
			list(APPEND sanitizers "thread")
		endif()
	endif()

	option(${option_prefix}_ENABLE_SANITIZER_MEMORY
		"${option_category}: Enable memory sanitizer" OFF)
	if(${option_prefix}_ENABLE_SANITIZER_MEMORY AND CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
		if("address" IN_LIST sanitizers
			OR "thread" IN_LIST sanitizers
			OR "leak" IN_LIST sanitizers
		)
			message(WARNING "${option_category}: Memory sanitizer does not work "
				"with address, thread and leak sanitizer enabled")
		else()
			list(APPEND sanitizers "memory")
		endif()
	endif()

	list(JOIN sanitizers "," list_of_sanitizers)
endif()

if(list_of_sanitizers)
	if(NOT "${list_of_sanitizers}" STREQUAL "")
		target_compile_options(sanitizer_options INTERFACE -fsanitize=${list_of_sanitizers})
		target_link_options(sanitizer_options INTERFACE -fsanitize=${list_of_sanitizers})
		message(STATUS "${option_category}: Enabled sanitizers: ${list_of_sanitizers}")
	endif()
endif()
