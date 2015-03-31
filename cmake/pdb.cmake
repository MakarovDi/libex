function (add_pdb EXE_NAME)
	# generate .pdb debug information with cv2pdb
	# MSVS generate it automatically
	if ((WIN32) AND (NOT MSVS))
		if (CMAKE_RUNTIME_OUTPUT_DIRECTORY) # Clion IDE use it
			set(BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
		elseif(EXECUTABLE_OUTPUT_PATH)      # user may set it
			set(BINARY_DIR ${EXECUTABLE_OUTPUT_PATH})
		elseif(CMAKE_BINARY_DIR)            # last resort
			set(BINARY_DIR ${CMAKE_BINARY_DIR})
		endif()

		set(CV2PDB_TOOL ${EX_SOURCE_DIRECTORY}/tools/cv2pdb.exe)

		if (EXISTS ${CV2PDB_TOOL})
			add_custom_command(TARGET ${EXE_NAME}
							   POST_BUILD
							   COMMAND ${CV2PDB_TOOL} ${BINARY_DIR}/${EXE_NAME}.exe
							   WORKING_DIRECTORY ${BINARY_DIR}
							   DEPENDS ${EXE_NAME}
			)
			message(STATUS "Enabled PDB-generating for ${EXE_NAME}")
		else()
			message(WARNING "cv2pdb tool is not available -> namespace debug doesn't work")
			# TODO: remove debug defination
		endif()
	endif()
endfunction()