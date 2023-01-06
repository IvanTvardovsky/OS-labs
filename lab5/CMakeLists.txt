add_executable(main2 library1.so library2.so)

add_executable(libraries src/functions1.c src/functions1.c include/functions.h)

target_include_directories(main2 PRIVATE include)

target_include_directories(libraries PRIVATE include)

add_dependencies(main2 libraries)