set(CMAKE_CXX_FLAGS "-lzmq")

add_executable(main main.cpp ./src/allocator_list.cpp ./src/allocator_mkk.cpp)