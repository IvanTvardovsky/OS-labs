add_executable(lab3 main.c src/general.c src/utils.c include/utils.h include/general.h)

target_include_directories(lab3 PRIVATE include)

target_link_libraries(lab3 PRIVATE Threads::Threads)