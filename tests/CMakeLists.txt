cmake_minimum_required(VERSION 3.22)

project(tests)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(lab2_test lab2_test.cpp 
../lab2/src/utils.c ../lab2/include/utils.h 
../lab2/src/parent.c ../lab2/include/parent.h)

add_executable(lab3_test lab3_test.cpp 
../lab3/src/utils.c ../lab3/include/utils.h 
../lab3/src/general.c ../lab3/include/general.h)

add_executable(lab4_test lab4_test.cpp 
../lab4/src/utils.c ../lab4/include/utils.h 
../lab4/src/parent.c ../lab4/include/parent.h)

target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_include_directories(lab2_test PRIVATE ../lab2/include)

add_test(lab2_test lab2_test)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

add_test(lab3_test lab3_test)

target_link_libraries(lab4_test PRIVATE GTest::GTest)
target_include_directories(lab4_test PRIVATE ../lab4/include)

add_test(lab4_test lab4_test)