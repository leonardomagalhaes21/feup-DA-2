cmake_minimum_required(VERSION 3.23)
project(proj2)

set(CMAKE_CXX_STANDARD 14)

add_executable(proj2 main.cpp
        Classes/Data.h
        Classes/Graph.h
        Classes/Data.cpp
        Classes/Menu.cpp
        Classes/TspManager.h
        Classes/TspManager.cpp
        Classes/MutablePriorityQueue.h
)
