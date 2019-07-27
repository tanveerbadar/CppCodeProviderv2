cmake_minimum_required(VERSION 3.0.0)
project(CppCodeProvider VERSION 1.0.0)

if(MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
