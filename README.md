# libex

Some code that I use frequently.

## Dependecies

No.

## Requirements ##

#### Linux/MinGW/Cygwin ####

 * CMake >= 2.8
 * Make
 * GCC (with C++11 support) / Clang
 
#### Windows ####

 * CMake >= 2.8
 * Microsoft Visual Studio 2013 Toolchain

## Build

Options:

 * UNICODE - set unicode as default project encoding:
    
        # cmake -DUNICODE=1
 
 * BUILD_SAMPLES - build all examples from ex/samples:
 
        # cmake -DBUILD_SAMPLES=1

#### CMake Project [Linux, MinGW, Cygwin] ####

Link it with your project:

``` cmake 

cmake_minimum_required(VERSION 2.8)

project(your_project)

if(UNICODE)
    add_definitions("-DUNICODE")
endif()

include(ex)

...

add_executable(your_project ...)

target_link_libraries(your_project ex)
```

#### MSVC/Windows ####

Generate project for MS Visual Studio with command:

    # cmake -G "Visual Studio 13"

## TODO ##

 - [ ] Changelog
 - [ ] Unit Tests (Google Test)
 - [ ] Examples
 - [ ] Doxygen
 - [ ] cppformat integration
 - [ ] spdlog integration


