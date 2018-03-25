include_directories(SYSTEM ${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)


add_executable(ExTests test1.cpp)


target_link_libraries(ExTests PRIVATE gtest gtest_main)