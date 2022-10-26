add_executable(lab2 include/parent.h include/utils.h main.c src/child.c src/parent.c src/utils.c)

target_include_directories(lab2 PRIVATE include)

cmake_minimum_required(VERSION 3.20)

project(OS_LABS C CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(lab2)

add_subdirectory(tests)