cmake_minimum_required(VERSION 3.28)
project(proj2)

set(CMAKE_CXX_STANDARD 17)

add_executable(proj2 main.cpp
        Classes/Data.h
        Classes/Graph.h
        Classes/Data.cpp)
