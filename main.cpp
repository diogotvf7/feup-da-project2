#include <iostream>
#include <iomanip>
#include <fstream>

#include "headers/Graph.h"
#include "headers/csv.h"
#include "headers/Menu.h"

using namespace std;


void runIntermediateGraphsEx3(const vector<string> &paths) {

    double initialPheromones = 0.03,
           evaporationRate = 0.1,
           pheromoneDeposit = 1;
    int numIterations = 200,
        numAnts = 25,
        ALPHA = 2,
        BETA = 1;

    ofstream file("aco-" + to_string(numIterations) + "iter" + to_string(numAnts) + "ants.txt");
    file << fixed << setprecision(0);

    file << "---------- Intermediate Graphs Results ----------" << endl;
    file << "Initial pheromones: " << initialPheromones << endl;
    file << "Evaporation rate: " << evaporationRate << endl;
    file << "Pheromone deposit: " << pheromoneDeposit << endl;
    file << "Number of iterations: " << numIterations << endl;
    file << "Number of ants: " << numAnts << endl;
    file << "ALPHA: " << ALPHA << endl;
    file << "BETA: " << BETA << endl << endl;

    for (const string &path : paths) {
        double elapsedTime;
        Graph *graph = new Graph();
        csv::readEdges(path, graph, false);
        vector<vector<double>> distanceCache(graph->getNodes().size(), vector<double>(graph->getNodes().size(), -1));
        vector<vector<double>> pheromoneTrails(graph->getNodes().size(), vector<double>(graph->getNodes().size(), initialPheromones));
        Path bestPath = measureExecutionTime(elapsedTime, *graph, &Graph::aco, pheromoneTrails, evaporationRate, pheromoneDeposit, numIterations, numAnts, ALPHA, BETA, distanceCache);
        file << "---------- " << path.substr(path.find_last_of('/') + 1, path.size()) << " ----------" << endl
             << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
             << setw(30) << left << "Path:";
        for (int i = 0; i < bestPath.nodes.size(); i++) {
            file << " " << bestPath.nodes[i];
            if (i % 30 == 0 && i > 0 && i + 1 < bestPath.nodes.size())
                file << endl << setw(30) << right << ' ';
        }
        file << endl << setw(30) << left << "Path total distance: " << bestPath.distance
             << endl << endl;

        if (stoi(path.substr(path.find_last_of('_') + 1, path.find_last_of('.'))) <= 200) {
            double enhancement = measureExecutionTime(elapsedTime, *graph, &Graph::apply2OptSwap, bestPath,
                                                      distanceCache, 250);
            file << "Executing 2-opt swap" << endl
                 << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
                 << setw(30) << left << "Path after 2-opt:";
            for (int i = 0; i < bestPath.nodes.size(); i++) {
                file << " " << bestPath.nodes[i];
                if (i % 30 == 0 && i > 0 && i + 1 < bestPath.nodes.size())
                    file << endl << setw(30) << right << ' ';
            }
            file << endl << setw(30) << left << "Path total distance: " << bestPath.distance << " ("
                 << enhancement * 100 << "%)"
                 << endl << endl;
        }
        delete graph;
    }
    file.close();
}

void printDistanceCache(const vector<vector<double>> &distanceCache, const std::string &outputPath) {
    ofstream file(outputPath);
    file << "Distance cache: " << endl;
    for (int i = 0; i < distanceCache.size(); i++) {
        if (i == 0) {
            for (int j = 0; j < distanceCache[i].size(); j++) {
                if (j == 0)
                    file << setw(11) << right << "|";
                file << setw(10) << j << "|";
            }
            file << endl;
            for (int j = 0; j < distanceCache[i].size(); j++)
                file << setw(10) << "__________";
        }
        for (int j = 0; j < distanceCache[i].size(); j++) {
            if (j == 0)
                file << endl << setw(10) << i << "| ";
            file << setw(10) << distanceCache[i][j] << "|";
        }
        file << setw(10) << i << " ";
    }
    file.close();
}

int main() {
    vector<string> paths = {
            "toy-graphs/shipping.csv",
            "toy-graphs/stadiums.csv",
            "toy-graphs/tourism.csv",
            "extra-graphs/edges_25.csv",
            "extra-graphs/edges_50.csv",
            "extra-graphs/edges_75.csv",
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
    menu.init();

//    vector<string> paths2 = {"extra-graphs/edges_25.csv",
//                             "extra-graphs/edges_50.csv",
//                             "extra-graphs/edges_75.csv",
//                             "extra-graphs/edges_100.csv",
//                             "extra-graphs/edges_200.csv",
//                             "extra-graphs/edges_300.csv",
//                             "extra-graphs/edges_400.csv",
//                             "extra-graphs/edges_500.csv",
//                             "extra-graphs/edges_600.csv",
//                             "extra-graphs/edges_700.csv",
//                             "extra-graphs/edges_800.csv",
//                             "extra-graphs/edges_900.csv"};
//    runIntermediateGraphsEx3(paths2);

    return 0;
}