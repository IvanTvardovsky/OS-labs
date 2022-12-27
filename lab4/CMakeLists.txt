add_executable(lab4 main.c src/parent.c include/utils.h src/utils.c include/parent.h)

target_include_directories(lab4 PRIVATE include)

add_executable(child src/child.c include/utils.h src/utils.c)

target_include_directories(child PRIVATE include)

add_dependencies(lab4 child)