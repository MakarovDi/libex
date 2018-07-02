include_directories(SYSTEM ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)
include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/include)


add_executable(ExTests
    ct/meta_str.cpp
    ct/char.cpp
    ct/charset.cpp
    ct/set_char.cpp
    ct/strlen.cpp
    ct/strfill.cpp
    ct/streq.cpp
    ct/substr.cpp
    ct/strcat.cpp
    ct/basename.cpp
    ct/math.cpp
    encoding/word16.cpp
    range_check.cpp
    expected.cpp
    container/ring_buffer.cpp)


target_link_libraries(ExTests PRIVATE ex gtest gtest_main)