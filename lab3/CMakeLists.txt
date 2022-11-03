cmake_minimum_required(VERSION 3.22)

project(lab3)

add_executable(lab3 src/main.c src/utils.c include/utils.h)

target_include_directories(lab3 PRIVATE include)