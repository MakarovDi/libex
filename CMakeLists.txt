cmake_minimum_required(VERSION 3.1.0)

# Define library name and version
set(PARENT_PROJECT ${PROJECT_NAME})

project(ex) # Initialize PROJECT_xxx variables

set(EX_VERSION_MAJOR     0)
set(EX_VERSION_MINOR     4)
set(EX_VERSION_REVISION  0)

set(CMAKE_CXX_STANDARD  14)

# compilation options
option(BUILD_TESTS   "Build the unit tests"    OFF)
option(BUILD_SAMPLES "Build the demo programs" OFF)


# Configure output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/bin)

# TODO: use [add_compile_warnings] in new CMake instead of this
# configure compiler options
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wpedantic")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wpedantic")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /WX /EHsc")

    # disable MS warning about safer *_s functions
    add_compile_options(/wd4996)

    if (BUILD_TESTS)
        # force this option to ON so that Google Test will use /MD instead of /MT
        # /MD is now the default for Visual Studio, so it should be our default, too
        set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)
    endif()
endif()

# Generate and use config.h file
configure_file (
    ${PROJECT_SOURCE_DIR}/config.in
    ${PROJECT_BINARY_DIR}/include/ex/config
    @ONLY                                          # replace VAR with pattern @VAR@ only (not ${VAR})
)
add_definitions("-DHAVE_CONFIG_H")                 # define HAVE_CONFIG_H for project

# define include path for internal usage
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include) # for config.h using

# Enumerate source files
set(SOURCES
    src/version.cpp
    src/placebo.cpp
    src/cprint.cpp
    src/stream/tmp.cpp
    src/stream/file.cpp
    src/stream/buffered.cpp
    src/stream/memory.cpp
    src/stream/interface.cpp
)

# Enumerate header files
set(HEADERS
    include/ex/algo
    include/ex/exception
    include/ex/expected
    include/ex/format
    include/ex/iterator/any_iterator
    include/ex/iterator/index_iterator
    include/ex/iterator/make
    include/ex/macro
    include/ex/placebo
    include/ex/platform/detect
    include/ex/platform/macro
    include/ex/scopeguard
    include/ex/string
    include/ex/version
    include/ex/container/pool
    include/ex/container/ring_buffer
    include/ex/interface
    include/ex/cprint
    include/ex/assert
    include/ex/semantic
    include/ex/policy/threading
    include/ex/policy/notice
    include/ex/policy/pool/size
    include/ex/policy/pool/destroy
    include/ex/range_check
    include/ex/ct
    include/ex/log/logger
    include/ex/log/stdstream
    include/ex/ct/string
    include/ex/ct/math
    include/ex/ct/meta_str
    include/ex/ct/char
    include/ex/ct/set_char
    include/ex/ct/streq
    include/ex/ct/strcat
    include/ex/ct/strfill
    include/ex/ct/charset
    include/ex/ct/substr
    include/ex/ct/strlen
    include/ex/ct/basename
    include/ex/log/autotag
    include/ex/meta/sequence
    include/ex/meta/pack
    include/ex/meta/selector
    include/ex/meta/concept
    include/ex/meta/math_type
    include/ex/meta/traits
    include/ex/common/type
    include/ex/common/policy
    include/ex/encoding/word16
    include/ex/random
    include/ex/window
    include/ex/utility
    include/ex/stream/interface
    include/ex/stream/file
    include/ex/stream/tmp
    include/ex/stream/buffered
    include/ex/stream/memory
)



# define and export library with name ex
add_library(ex STATIC ${SOURCES} ${HEADERS})

# use linker for C++ (CXX)
set_target_properties(ex PROPERTIES LINKER_LANGUAGE CXX
                                    CXX_STANDARD 14
                                    CXX_STANDARD_REQUIRED ON)

# populate ex headers
target_include_directories(ex PUBLIC ${PROJECT_SOURCE_DIR}/include)


# initialize external libs
add_subdirectory(external)

# lib {fmt} in header only mode
target_link_libraries(ex PUBLIC fmt::fmt-header-only)


# unit tests
if (BUILD_TESTS)
    add_subdirectory(test)
    message(STATUS "Test building enabled")
endif()


# Build samples
if(BUILD_SAMPLES)
    add_subdirectory(samples)
    message(STATUS "Samples building enabled")
endif()




