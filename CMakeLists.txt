cmake_minimum_required(VERSION 3.0.0)
project(helloWorld VERSION 0.1.0)


set(CMAKE_GENERATOR "Unix Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")


add_subdirectory(lib/sum)


file(GLOB HW_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
add_executable(helloWorld ${HW_SRC})

#target_include_directories(helloWorld PUBLIC /lib/sum)
# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (helloWorld LINK_PUBLIC sum_lib)
