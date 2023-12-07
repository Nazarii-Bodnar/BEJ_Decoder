cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

project(BEJDecoder VERSION 1.0)
add_executable(decode main.c getFromDictionary.c BEJDecoder.c)

include(CTest)
add_subdirectory(external)
add_subdirectory(tests)