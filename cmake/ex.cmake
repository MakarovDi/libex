##
## Ex-Lib cmake include file
## for automatically setup user project
##

# Export global variable with path to Ex
set(EX_SOURCE_DIRECTORY "${CMAKE_MODULE_PATH}/.." CACHE STRING "EX Library Source Directory")

include(pdb) # load add_pdb function

# Override standart 'add_executable' function
# for auto PDB-generating on MinGW in DEBUG mode
function (add_executable EXE_NAME)
	_add_executable(${EXE_NAME} ${ARGN})
	add_pdb(${EXE_NAME})
endfunction()


# Passing include directory to compiler
include_directories(${EX_SOURCE_DIRECTORY}/include)

# Run CMakeList.txt for Ex
add_subdirectory(${EX_SOURCE_DIRECTORY})