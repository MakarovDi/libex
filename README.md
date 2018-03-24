# libex

Some building blocks which I use frequently.

## Dependecies

No.

## Submodules

* **{fmt}**: a modern formatting library http://fmtlib.net

## Requirements ##

#### Linux/MinGW/Cygwin ####

 * CMake >= 3.1
 * Make
 * GCC (with C++14 support) / Clang
 
#### Windows ####

 * CMake >= 3.1
 * Microsoft Visual Studio 2015 Toolchain

## Configuration

Options:

 * BUILD_SAMPLES - build all examples from ex/samples:
 
		# cmake -DBUILD_SAMPLES=1

## Usage

#### Get code

	# git clone https://github.com/MakarovDi/libex.git ex
	# cd ./ex
	# git checkout v0.3.0
	# git submodule init
	# git submodule update

#### CMake Project [Linux/MinGW/Cygwin] ####

Link it with a project:

``` cmake 
cmake_minimum_required(VERSION 3.1)

project(your_project)


set(CMAKE_CXX_STANDARD 14)


add_subdirectory(ex)

...

add_executable(your_project ...)

target_link_libraries(your_project ex)
```

#### MSVC/Windows ####

Generate project for MS Visual Studio with command:

    # cmake -G "Visual Studio 14"


