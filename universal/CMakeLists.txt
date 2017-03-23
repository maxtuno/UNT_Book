cmake_minimum_required(VERSION 3.6)
project(universal)

enable_language(ASM_NASM)

set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f macho64")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -Os -DNDEBUG -march=native -mtune=native")
set(CMAKE_C_COMPILER /usr/local/bin/gcc-6)

set(SOURCE_FILES main.c universal.asm)
add_executable(universal ${SOURCE_FILES})