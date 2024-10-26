##set required cmake standard
cmake_minimum_required(VERSION 3.27)


message(STATUS "CMake version: ${CMAKE_VERSION}")
message("Building all projects...")

##set project name
project(ASP)


set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Practicals)
add_subdirectory(Assignment)