## Configurable:
##
##  UNICODE = 1   -> use unicode by default
##  BUILD_SAMPLES -> compile samples
cmake_minimum_required(VERSION 2.8)

# Define library name and version
set(PARENT_PROJECT ${PROJECT_NAME})

project(ex) # Initialize PROJECT_xxx variables

set(EX_VERSION_MAJOR     0)
set(EX_VERSION_MINOR     1)
set(EX_VERSION_REVISION  2)

# Configure output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/bin)

# Works only with C++11 (-std=c++11)
# Show all warnings (-Wall)
# All warnnings MUST be resolved (-pedantic)
# TODO: add -pedantic on GCC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

# Generate and use config.h file
configure_file (
    ${PROJECT_SOURCE_DIR}/config.in
    ${PROJECT_BINARY_DIR}/include/ex/config
    @ONLY                                          # replace VAR with pattern @VAR@ only (not ${VAR})
)
add_definitions("-DHAVE_CONFIG_H")                 # define HAVE_CONFIG_H for project
include_directories(${PROJECT_BINARY_DIR}/include) # for config.h using

# Enumerate source files
set(SOURCES
    src/debug.cpp
    src/version.cpp
)

# Tell where find headers
include_directories(${PROJECT_SOURCE_DIR}/include)


# Enumerate header files
set(HEADERS
    include/ex/iterator
    include/ex/string
    include/ex/debug
    include/ex/version
)


# define and export library with name ex
add_library(ex STATIC ${SOURCES} ${HEADERS} src/string.cpp include/ex/exception include/ex/macro)

# use linker for C++ (CXX)
set_target_properties(ex PROPERTIES LINKER_LANGUAGE CXX)

# Some debug settings
if (WIN32)
	# debug namespace use imagehlp and pdb on Windows
	target_link_libraries(ex imagehlp)
	# use debug symbols for pdb-generation
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()


# Check for unicode build
if(UNICODE)
    add_definitions("-DUNICODE")
endif()


# Build samples if need
if(BUILD_SAMPLES)
    add_subdirectory(samples)
    message(STATUS "Samples building enabled")
endif()




