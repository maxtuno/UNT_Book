cmake_minimum_required(VERSION 3.0)
project(unt)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "-std=c++14")

find_package(OpenCL REQUIRED)

set(SOURCE_FILES main.cpp peqnp/unt.hpp)
add_executable(unt ${SOURCE_FILES})
target_link_libraries(unt ${OpenCL_LIBRARIES})