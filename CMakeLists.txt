cmake_minimum_required(VERSION 3.6)
project(mazeSolver)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Maze.cpp Maze.h Solver.h FillSolver.cpp FillSolver.h Node.h AStarSolver.cpp AStarSolver.h)
add_executable(mazeSolver ${SOURCE_FILES})