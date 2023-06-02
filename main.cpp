#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

#include "headers/Graph.h"
#include "headers/csv.h"
#include "headers/Menu.h"

using namespace std;

int main() {
/*    vector<string> paths = {
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

    Graph *graph = new Graph();
    double elapsedTime;
    csv::readEdges("extra-graphs/edges_25.csv", graph);


/*
    ofstream file("/home/diogotvf7/Documents/2a2s/da/DA-Project2/intermediate-graphs-results-ex3.txt");
    file << std::fixed << std::setprecision(0);

    vector<string> paths = {"extra-graphs/edges_25.csv",
                            "extra-graphs/edges_50.csv",
                            "extra-graphs/edges_100.csv",
                            "extra-graphs/edges_200.csv",
                            "extra-graphs/edges_300.csv",
                            "extra-graphs/edges_400.csv",
                            "extra-graphs/edges_500.csv",
                            "extra-graphs/edges_600.csv",
                            "extra-graphs/edges_700.csv",
                            "extra-graphs/edges_800.csv",
                            "extra-graphs/edges_900.csv"};

    double initialPheromones = 0.3, evaporationRate = 0.60, pheromoneDeposit = 2;
    int numIterations = 200, numAnts = 5, ALPHA = 1, BETA = 2;

    for (const string &path : paths) {
        double elapsedTime;
        Graph *graph = new Graph();
        csv::readEdges(path, graph);
        vector<vector<double>> pheromoneTrails(graph->getNodes().size(), vector<double>(graph->getNodes().size(), initialPheromones));
        AntPath bestPath = measureExecutionTime(elapsedTime, *graph, &Graph::performACO, pheromoneTrails, evaporationRate, pheromoneDeposit, numIterations, numAnts, ALPHA, BETA);
        file << "---------- " << path.substr(path.find_last_of('/'), path.size()) << " ----------" << endl
             << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
             << setw(30) << left << "Path:";
        for (int i = 0; i < bestPath.path.size(); i++) {
            file << " " << bestPath.path[i];
            if (i % 10 == 0 && i > 0 && i + 1 < bestPath.path.size())
                file << endl << setw(30) << right << ' ';
        }
        file << endl << setw(30) << left << "Path total distance: " << bestPath.distance
             << endl << endl;
        delete graph;
    }
    file.close();
*/

    return 0;
}