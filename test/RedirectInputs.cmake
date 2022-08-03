if(NOT REDIRECT_WORKING_DIR)
	message(FATAL_ERROR "REDIRECT_WORKING_DIR option hasn't been set")
endif()

if(NOT REDIRECT_TARGET_FILE)
	message(FATAL_ERROR "REDIRECT_TARGET_FILE option hasn't been set")
endif()

if(NOT REDIRECT_ARGS_FILE)
	message(FATAL_ERROR "REDIRECT_ARGS_FILE option hasn't been set")
endif()

if(NOT REDIRECT_INPUT_FILE)
	message(FATAL_ERROR "REDIRECT_INPUT_FILE option hasn't been set")
endif()

if(NOT EXISTS ${REDIRECT_WORKING_DIR})
	message(FATAL_ERROR "REDIRECT_WORKING_DIR (${REDIRECT_WORKING_DIR}) doesn't exist")
endif()

if(NOT EXISTS ${REDIRECT_TARGET_FILE})
	message(FATAL_ERROR "REDIRECT_TARGET_FILE (${REDIRECT_TARGET_FILE}) doesn't exist")
endif()

if(EXISTS ${REDIRECT_ARGS_FILE})
	file(STRINGS ${REDIRECT_ARGS_FILE} redirect_args)
endif()

set(redirect_wait_timeout 5)

if(EXISTS ${REDIRECT_INPUT_FILE})
	execute_process(
		COMMAND ${REDIRECT_TARGET_FILE} ${redirect_args}
		WORKING_DIRECTORY ${REDIRECT_WORKING_DIR}
		TIMEOUT ${redirect_wait_timeout}
		INPUT_FILE ${REDIRECT_INPUT_FILE}
		COMMAND_ERROR_IS_FATAL ANY
	)
else()
	# Since `execute_prcess` fails if `INPUT_FILE` doesn't exist, we need to separate the case where
	# the executable doesn't need standard input
	execute_process(
		COMMAND ${REDIRECT_TARGET_FILE} ${redirect_args}
		WORKING_DIRECTORY ${REDIRECT_WORKING_DIR}
		TIMEOUT ${redirect_wait_timeout}
		COMMAND_ERROR_IS_FATAL ANY
	)
endif()


