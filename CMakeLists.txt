cmake_minimum_required(VERSION 3.23)
project(DA-Project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA-Project2
        .vscode/tasks.json
        dataset/Toy-Graphs/shipping.csv
        dataset/Toy-Graphs/stadiums.csv
        dataset/Toy-Graphs/tourism.csv
        main.cpp
        main.exe
        README.md source/Utils.cpp headers/Utils.h source/Graph.cpp headers/Graph.h headers/NodeEdge.h source/NodeEdge.cpp  headers/MutablePriorityQueue.h source/MutablePriorityQueue.cpp)
