cmake_minimum_required(VERSION 3.12)
project(TSPSolver)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")

add_executable(tsp ${SOURCES})
