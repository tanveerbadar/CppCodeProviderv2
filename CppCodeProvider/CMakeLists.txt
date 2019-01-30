cmake_minimum_required(VERSION 3.5)
project(CppCodeProvider)

FIND_PACKAGE(Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17" )

FILE(GLOB_RECURSE SOURCES features/*.cpp)
FILE(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_library(CppCodeProviderLib ${SOURCES})
add_executable(CppCodeProvider CppCodeProvider.cpp)
add_executable(CppCodeProviderTests ${TEST_SOURCES})

target_link_libraries(CppCodeProviderTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} CppCodeProviderLib)
target_link_libraries(CppCodeProvider CppCodeProviderLib)