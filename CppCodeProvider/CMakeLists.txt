cmake_minimum_required(VERSION 3.5)

cmake_policy(SET CMP0074 NEW)
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(CMAKE_CXX_STANDARD 14)
set(DEBUG ON)

enable_testing()
add_test(NAME CppCodeProviderTests COMMAND CppCodeProviderTests)

FIND_PACKAGE(Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)

FILE(GLOB_RECURSE SOURCES features/*.cpp)
FILE(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_library(CppCodeProviderLib ${SOURCES} utils/write_helpers.cpp formatters/formatter_settings.cpp)
add_executable(CppCodeProvider CppCodeProvider.cpp)
add_executable(CppCodeProviderTests ${TEST_SOURCES})

target_link_libraries(CppCodeProviderTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} CppCodeProviderLib)
target_include_directories(CppCodeProviderTests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(CppCodeProvider CppCodeProviderLib)