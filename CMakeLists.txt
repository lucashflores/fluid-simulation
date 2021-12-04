cmake_minimum_required(VERSION 3.13)
project(fluid-simulation)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(fluid-simulation main.cpp ${SOURCES})
set_target_properties(fluid-simulation PROPERTIES RUNTIME_OUTPUT_DIRECTORY "./")

include_directories (include)