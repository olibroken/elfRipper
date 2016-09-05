cmake_minimum_required(VERSION 3.6)
project(elfRipper)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp IO.cpp IO.h elf_headers.h)
add_executable(elfRipper ${SOURCE_FILES})