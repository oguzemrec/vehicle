cmake_minimum_required(VERSION 3.15)
project(unittest VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")

add_definitions("-std=c++17")


#file(GLOB sources   ${PROJECT_SOURCE_DIR}/*.cpp
#${PROJECT_SOURCE_DIR}/../src/*.cpp
#${PROJECT_SOURCE_DIR}/../src/*.h)

set(sources main.cpp  sensor_test.cpp ../src/sensors.h  ../src/sensors.cpp)


include(${CMAKE_BINARY_DIR}/cmake-build-debug/conanbuildinfo.cmake)
conan_basic_setup()
#conan install .. -s build_type=Debug -s compiler.libcxx=libc++ -s cppstd=20 --install-folder=cmake-build-debug --build missing

#find_package(GTest)
# Use the global target

#INCLUDE( ${CMAKE_SOURCE_DIR}/cmake-module/CodeCoverage.cmake )

#append_coverage_compiler_flags()
#add_test(NAME unittest COMMAND unittest)

add_executable(unittest ${sources})
target_link_libraries(unittest ${CONAN_LIBS})

