#include <iostream>
#include "headers/Graph.h"
#include "headers/csv.h"
#include "headers/Menu.h"
#include <chrono>

int main() {
/*    std::vector<std::string> paths = {
            "toy-graphs/shipping.csv",
            "toy-graphs/stadiums.csv",
            "toy-graphs/tourism.csv",
            "extra-graphs/edges_25.csv",
            "extra-graphs/edges_50.csv",
            "extra-graphs/edges_100.csv",
            "extra-graphs/edges_200.csv",
            "extra-graphs/edges_300.csv",
            "extra-graphs/edges_400.csv",
            "extra-graphs/edges_500.csv",
            "extra-graphs/edges_600.csv",
            "extra-graphs/edges_700.csv",
            "extra-graphs/edges_800.csv",
            "extra-graphs/edges_900.csv",
            "real-graphs/graph1/",
            "real-graphs/graph2/",
            "real-graphs/graph3/",
            };
    Menu menu = Menu(paths);
    menu.init();*/
    

    Graph graph = Graph();
    csv::readEdges("extra-graphs/edges_25.csv", &graph);
/*    csv::readNodes("real-graphs/graph1/nodes.csv", &graph);
    csv::readEdges("real-graphs/graph1/edges.csv", &graph);*/

    std::vector<std::vector<double>> pheromoneTrails(graph.getNodes().size(), std::vector<double>(graph.getNodes().size(), 0.3));

    AntPath bestPath = graph.performACO(pheromoneTrails,
                                 0.60,
                                 1,
                                 2500,
                                 20,
                                 1,
                                 1
                                );

    std::cout << "Best path: ";
    for (int i : bestPath.path)
        std::cout << i << " ";
    std::cout << std::endl << "Path cost: " << bestPath.distance << std::endl;

    std::cout << std::endl << std::endl << std::endl;

    double bestCost = INF;
    std::vector<int> path = graph.approxTSPTour(bestCost);
    std::cout << "Best path: ";
    for (int i : path)
        std::cout << i << " ";
    std::cout << std::endl << "Path cost: " << bestCost << std::endl;

    return 0;
}