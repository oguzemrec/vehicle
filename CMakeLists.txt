cmake_minimum_required(VERSION 3.0.0)
project(vehicle VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_GENERATOR "Unix Makefiles")
message("generator is set to ${CMAKE_GENERATOR}")

file(GLOB HW_SRC CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h)
add_executable(vehicle ${HW_SRC})

