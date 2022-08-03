if(NOT c_samples_all_targets)
	message(FATAL_ERROR "Provide the list of targets to test by setting the c_samples_all_targets variable")
endif()

# We add one test per target which simply runs the executable with the specified command line arguments
# and stdin input.
#
# However, `add_test` doesn't support stream redirection out of the box.
# As far as I am aware, the only cross-platform way to do this is to call the `execute_process`
# function. The issue is that `execute_process` runs during configuration stage while CTest runs after the
# build stage.
#
# As a result, we come up with the following hack: duing testing pass a custom script to a separate
# CMake process which in turn will run the executable using `execute_process`.
# If needed, the list of command line arguments and the stdin text can be provided using files
# `test/data/${your_target_name}_args.txt` and `test/data/${your_target_name}_stdin.txt`
# respectively.
#
# NOTE: The existance of these file is checked during testing but not configuration stage,
# which may or may not be the desired behavior.

foreach(sample_target ${c_samples_all_targets})
	add_test(
		NAME test_${sample_target}
		COMMAND ${CMAKE_COMMAND}
			-D REDIRECT_WORKING_DIR=$<TARGET_FILE_DIR:${sample_target}>
			-D REDIRECT_TARGET_FILE=$<TARGET_FILE:${sample_target}>
			-D REDIRECT_ARGS_FILE=${PROJECT_SOURCE_DIR}/test/data/${sample_target}_args.txt
			-D REDIRECT_INPUT_FILE=${PROJECT_SOURCE_DIR}/test/data/${sample_target}_stdin.txt
			-P "${PROJECT_SOURCE_DIR}/test/RedirectInputs.cmake"
	)
endforeach()
