cmake_minimum_required(VERSION 3.5)
project(CppCodeProvider)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )

FILE(GLOB_RECURSE SOURCES features/*.cpp)

add_executable(CppCodeProvider ${SOURCES} CppCodeProvider.cpp)