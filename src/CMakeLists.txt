cmake_minimum_required(VERSION 3.5)

cmake_policy(SET CMP0074 NEW)
set(CMAKE_CXX_STANDARD 14)
set(DEBUG ON)

FILE(GLOB_RECURSE SOURCES features/*.cpp)

add_library(CppCodeProviderLib ${SOURCES} utils/write_helpers.cpp formatters/formatter_settings.cpp)
add_executable(CppCodeProvider CppCodeProvider.cpp)
target_link_libraries(CppCodeProvider CppCodeProviderLib)