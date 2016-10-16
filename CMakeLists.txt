## Configurable:
##
##  UNICODE = 1   -> use unicode
##  BUILD_SAMPLES -> compile samples
cmake_minimum_required(VERSION 2.8)

# Define library name and version
set(PARENT_PROJECT ${PROJECT_NAME})

project(ex) # Initialize PROJECT_xxx variables

set(EX_VERSION_MAJOR     0)
set(EX_VERSION_MINOR     1)
set(EX_VERSION_REVISION  4)

# Configure output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/bin)


IF(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions("-DNDEBUG")
ENDIF()


# Works only with C++11 (-std=c++11)
# Show all warnings (-Wall)
# All warnnings MUST be resolved (-Wpedantic)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wconversion -Wpedantic")

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
    src/placebo.cpp
    src/platform.cpp
    src/string.cpp
    src/version.cpp
    src/cprint.cpp
    src/assert.cpp
    src/format.cc)

# Tell where find headers
include_directories(${PROJECT_SOURCE_DIR}/include)


# Enumerate header files
set(HEADERS
    include/ex/algo
    include/ex/exception
    include/ex/expected
    include/ex/format
    include/ex/iterator
    include/ex/macro
    include/ex/placebo
    include/ex/platform
    include/ex/scopeguard
    include/ex/string
    include/ex/version
    include/ex/pool
    include/ex/interface
    include/ex/policy/threading
    include/ex/policy/pool
    include/ex/cprint
    include/ex/assert
    include/ex/semantic
    include/ex/policy/notice
    include/ex/range_check
    include/ex/ct)


# define and export library with name ex
add_library(ex STATIC ${SOURCES} ${HEADERS})

# use linker for C++ (CXX)
set_target_properties(ex PROPERTIES LINKER_LANGUAGE CXX)

# Some debug settings
#if (WIN32)
#    # debug namespace use imagehlp and pdb on Windows
#    target_link_libraries(ex imagehlp)
#    # use debug symbols for pdb-generation
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#endif()


# Check for unicode build
if(UNICODE)
    add_definitions("-DUNICODE")
endif()


# Build samples if need
if(BUILD_SAMPLES)
    add_subdirectory(samples)
    message(STATUS "Samples building enabled")
endif()




