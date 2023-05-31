cmake_minimum_required(VERSION 3.23)
project(projeto_da)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto_da
        dataset/real-graphs/graph1/nodes.csv
        dataset/real-graphs/graph1/edges.csv
        dataset/real-graphs/graph2/nodes.csv
        dataset/real-graphs/graph2/edges.csv
        dataset/real-graphs/graph3/nodes.csv
        dataset/real-graphs/graph3/edges.csv

        dataset/toy-graphs/shipping.csv
        dataset/toy-graphs/stadiums.csv
        dataset/toy-graphs/tourism.csv

        dataset/extra-graphs/edges_25.csv
        dataset/extra-graphs/edges_50.csv
        dataset/extra-graphs/edges_75.csv
        dataset/extra-graphs/edges_100.csv
        dataset/extra-graphs/edges_200.csv
        dataset/extra-graphs/edges_300.csv
        dataset/extra-graphs/edges_400.csv
        dataset/extra-graphs/edges_500.csv
        dataset/extra-graphs/edges_600.csv
        dataset/extra-graphs/edges_700.csv
        dataset/extra-graphs/edges_800.csv
        dataset/extra-graphs/edges_900.csv

        main.cpp
        headers/csv.h
        source/csv.cpp
        headers/Graph.h
        source/Graph.cpp
        headers/NodeEdge.h
        source/NodeEdge.cpp
        headers/Coordinate.h
        source/Coordinate.cpp
        headers/MutablePriorityQueue.h
        source/MutablePriorityQueue.cpp
        headers/Menu.h source/Menu.cpp)