cmake_minimum_required(VERSION 3.6)
project(unt)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)

add_executable(unt ${SOURCE_FILES})
target_link_libraries(unt tommath)