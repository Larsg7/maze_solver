cmake_minimum_required(VERSION 3.6)
project(mazeSolver)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Maze.cpp Maze.h)
add_executable(mazeSolver ${SOURCE_FILES})