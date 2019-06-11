cmake_minimum_required(VERSION 3.5)

set(BOOST_INCLUDEDIR E:/boost/boost_1_67_0/boost_1_67/include)
set(BOOST_LIBRARYDIR E:/boost/boost_1_67_0/boost_1_67/lib)
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Boost 1.60.0 COMPONENTS unit_test_framework REQUIRED)

include_directories(${BOOST_INCLUDEDIR})
FILE(GLOB_RECURSE SOURCES features/*.cpp)
FILE(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_library(CppCodeProviderLib ${SOURCES} utils/write_helpers.cpp formatters/formatter_settings.cpp)
add_executable(CppCodeProvider CppCodeProvider.cpp)
add_executable(CppCodeProviderTests ${TEST_SOURCES})

target_link_libraries(CppCodeProviderTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} CppCodeProviderLib)
target_link_libraries(CppCodeProvider CppCodeProviderLib)