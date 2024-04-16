cmake_minimum_required(VERSION 3.14.0)

project(modern_cpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD  20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(c17)
target_sources(c17 PRIVATE cpp17.cpp)
add_executable(c20)
target_sources(c20 PRIVATE cpp20.cpp)
