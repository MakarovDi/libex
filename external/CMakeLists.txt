add_subdirectory(fmt)


if (BUILD_TESTS)
    # force this option to ON so that Google Test will use /MD instead of /MT
    # /MD is now the default for Visual Studio, so it should be our default, too
    set(gtest_force_shared_crt ON CACHE BOOL "Always use msvcrt.dll" FORCE)

    # initialize googletest framework
    add_subdirectory(googletest)

    # ingnore warnings for googletest's code
    if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set_property(TARGET gtest APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
        set_property(TARGET gtest_main APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
    endif()
endif()
