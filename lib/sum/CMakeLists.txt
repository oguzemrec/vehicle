cmake_minimum_required(VERSION 3.10)

# set the project name
project(Sum)


file(GLOB SUM_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (sum_lib ${SUM_SRC})

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (sum_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(main_sum ${SUM_SRC})


