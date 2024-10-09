##set required cmake standard
cmake_minimum_required(VERSION 3.22)



set(CMAKE_CXX_STANDARD 20)


project(ASP)


#set output file path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(Worksheet0)
add_subdirectory(Worksheet1)
# add_subdirectory(Worksheet2)


