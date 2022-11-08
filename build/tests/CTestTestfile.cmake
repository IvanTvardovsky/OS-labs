# CMake generated Testfile for 
# Source directory: /home/tvard/os/OS-labs/tests
# Build directory: /home/tvard/os/OS-labs/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[lab3_test]=] "lab3_test")
set_tests_properties([=[lab3_test]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/tvard/os/OS-labs/tests/CMakeLists.txt;22;add_test;/home/tvard/os/OS-labs/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
