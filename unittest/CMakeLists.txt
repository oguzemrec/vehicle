cmake_minimum_required(VERSION 3.15)
project(unittest VERSION 0.1.0)

add_definitions("-std=c++11")

set(sources main.cpp hello_test.cpp ../hello.cpp ../hello.h)


include(${CMAKE_BINARY_DIR}/cmake-build-debug/conanbuildinfo.cmake)
conan_basic_setup()




find_package(GTest)
# Use the global target

add_executable(unittest ${sources})
target_link_libraries(unittest ${CONAN_LIBS})


