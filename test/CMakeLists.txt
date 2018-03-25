include_directories(SYSTEM ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/include)


add_executable(ExTests
    ct/strcat.cpp
    ct/meta_str.cpp
    ct/char.cpp
    ct/charset.cpp
    ct/set_char.cpp
    ct/strlen.cpp
    ct/strfill.cpp)


target_link_libraries(ExTests PRIVATE gtest gtest_main)