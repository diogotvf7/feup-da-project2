#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

#include "headers/Graph.h"
#include "headers/csv.h"
#include "headers/Menu.h"

using namespace std;


void runIntermediateGraphsEx3(const vector<string> &paths) {
    ofstream file("/home/diogotvf7/Documents/2a2s/da/DA-Project2/intermediate-graphs-results-ex3.txt");
    file << fixed << setprecision(0);

    double initialPheromones = 0.03, evaporationRate = 0.1, pheromoneDeposit = 1;
    int numIterations = 1000, numAnts = 25, ALPHA = 1, BETA = 1;

    for (const string &path : paths) {
        double elapsedTime, dist;
        Graph *graph = new Graph();
        csv::readEdges(path, graph, false);
        vector<vector<double>> distanceCache(graph->getNodes().size(), vector<double>(graph->getNodes().size(), -1));
        vector<vector<double>> pheromoneTrails(graph->getNodes().size(), vector<double>(graph->getNodes().size(), initialPheromones));
        AntPath bestPath = measureExecutionTime(elapsedTime, *graph, &Graph::performACO, pheromoneTrails, evaporationRate, pheromoneDeposit, numIterations, numAnts, ALPHA, BETA, distanceCache);
        file << "---------- " << path.substr(path.find_last_of('/') + 1, path.size()) << " ----------" << endl
             << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
             << setw(30) << left << "Path:";
        for (int i = 0; i < bestPath.path.size(); i++) {
            file << " " << bestPath.path[i];
            if (i % 10 == 0 && i > 0 && i + 1 < bestPath.path.size())
                file << endl << setw(30) << right << ' ';
        }
        file << endl << setw(30) << left << "Path total distance: " << bestPath.distance
             << endl << endl;

        graph->apply2OptSwap(bestPath, distanceCache);
        file << setw(30) << left << "Path after 2-opt:";
        for (int i = 0; i < bestPath.path.size(); i++) {
            file << " " << bestPath.path[i];
            if (i % 10 == 0 && i > 0 && i + 1 < bestPath.path.size())
                file << endl << setw(30) << right << ' ';
        }
        file << endl << setw(30) << left << "Path total distance: " << bestPath.distance
             << endl << endl;

        graph->approxTSPTour(dist);
        file << setw(30) << left << "Approx TSP tour:";

        //print distance cache as 2d matrix

        file << "Distance cache for " << path.substr(path.find_last_of('/') + 1, path.size()) << endl;
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
        file << endl;
        delete graph;
    }
    file.close();
}

void runIntermediateGraphsEx2(const vector<string> &paths) {
    ofstream file("/home/diogotvf7/Documents/2a2s/da/DA-Project2/intermediate-graphs-results-ex2.txt");
    file << fixed << setprecision(0);

    for (const string &path : paths) {
        double elapsedTime, dist;
        Graph *graph = new Graph();
        csv::readEdges(path, graph);
        std::vector<int> bestPath = measureExecutionTime(elapsedTime, *graph, &Graph::approxTSPTour, dist);
        file << "---------- " << path.substr(path.find_last_of('/') + 1, path.size()) << " ----------" << endl
             << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
             << setw(30) << left << "Path:";
        for (int i = 0; i < bestPath.size(); i++) {
            file << " " << bestPath[i];
            if (i % 10 == 0 && i > 0 && i + 1 < bestPath.size())
                file << endl << setw(30) << right << ' ';
        }
        file << endl << setw(30) << left << "Path total distance: " << dist
             << endl << endl;
        delete graph;
    }
    file.close();
}

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

    vector<string> paths = {"extra-graphs/edges_25.csv",
                            /*"extra-graphs/edges_50.csv",
                            "extra-graphs/edges_100.csv",
                            "extra-graphs/edges_200.csv",
                            "extra-graphs/edges_300.csv",
                            "extra-graphs/edges_400.csv",
                            "extra-graphs/edges_500.csv",
                            "extra-graphs/edges_600.csv",
                            "extra-graphs/edges_700.csv",
                            "extra-graphs/edges_800.csv",
                            "extra-graphs/edges_900.csv"*/};

//    runIntermediateGraphsEx2(paths);
    runIntermediateGraphsEx3(paths);

    return 0;
}
