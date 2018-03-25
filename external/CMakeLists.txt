add_subdirectory(fmt)


if (BUILD_TESTS)
    # initialize googletest framework
    add_subdirectory(googletest)
    # ingnore warnings for googletest's code
    set_property(TARGET gtest APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
    set_property(TARGET gtest_main APPEND_STRING PROPERTY COMPILE_FLAGS " -w")
endif()
