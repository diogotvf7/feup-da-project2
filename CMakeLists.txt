cmake_minimum_required(VERSION 3.23)
project(projeto_da)

set(CMAKE_CXX_STANDARD 14)

add_executable(projeto_da
        .idea/.gitignore
        .idea/modules.xml
        .idea/projeto-da.iml
        .idea/vcs.xml
        .idea/workspace.xml
        .vscode/tasks.json
        dataset/Toy-Graphs/shipping.csv
        dataset/Toy-Graphs/stadiums.csv
        dataset/Toy-Graphs/tourism.csv
        main.cpp
        main.exe
        README.md source/Utils.cpp headers/Utils.h source/Graph.cpp headers/Graph.h headers/NodeEdge.h source/NodeEdge.cpp  headers/MutablePriorityQueue.h source/MutablePriorityQueue.cpp)
