#include <iostream>
#include <iomanip>
#include <fstream>

#include "headers/Graph.h"
#include "headers/csv.h"
#include "headers/Menu.h"

using namespace std;


void runIntermediateGraphsEx3(const vector<string> &paths) {
    ofstream file("/home/diogotvf7/Documents/2a2s/da/DA-Project2/intermediate-graphs-results-ex3.txt");
    file << fixed << setprecision(0);

    double initialPheromones = 0.03, evaporationRate = 0.1, pheromoneDeposit = 1;
    int numIterations = 75, numAnts = 10, ALPHA = 1, BETA = 1;

    for (const string &path : paths) {
        double elapsedTime;
        Graph *graph = new Graph();
        csv::readEdges(path, graph, false);
        vector<vector<double>> distanceCache(graph->getNodes().size(), vector<double>(graph->getNodes().size(), -1));
        vector<vector<double>> pheromoneTrails(graph->getNodes().size(), vector<double>(graph->getNodes().size(), initialPheromones));
        Path bestPath = measureExecutionTime(elapsedTime, *graph, &Graph::performACO, pheromoneTrails, evaporationRate, pheromoneDeposit, numIterations, numAnts, ALPHA, BETA, distanceCache);
        file << "---------- " << path.substr(path.find_last_of('/') + 1, path.size()) << " ----------" << endl
             << "Executing ACO with " << numAnts << " ants for " << numIterations << " iterations" << endl
             << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
             << setw(30) << left << "Path:";
        for (int i = 0; i < bestPath.nodes.size(); i++) {
            file << " " << bestPath.nodes[i];
            if (i % 10 == 0 && i > 0 && i + 1 < bestPath.nodes.size())
                file << endl << setw(30) << right << ' ';
        }
        file << endl << setw(30) << left << "Path total distance: " << bestPath.distance
             << endl << endl;

        double enhancement = measureExecutionTime(elapsedTime, *graph, &Graph::apply2OptSwap, bestPath, distanceCache, 20);
        file << "Executing 2-opt swap" << endl
             << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
             << setw(30) << left << "Path after 2-opt:";
        for (int i = 0; i < bestPath.nodes.size(); i++) {
            file << " " << bestPath.nodes[i];
            if (i % 10 == 0 && i > 0 && i + 1 < bestPath.nodes.size())
                file << endl << setw(30) << right << ' ';
        }
        file << endl << setw(30) << left << "Path total distance: " << bestPath.distance << " (" << enhancement * 100 << "%)"
             << endl << endl;

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
                            "extra-graphs/edges_900.csv"};

//    runIntermediateGraphsEx2(paths);
//    runIntermediateGraphsEx3(paths);
    fstream file("/home/diogotvf7/Documents/2a2s/da/DA-Project2/dataset/real-graphs/graph1/results.txt", ios::app);
    file << fixed << setprecision(0);
    double initialPheromones = 0.03, evaporationRate = 0.1, pheromoneDeposit = 1;
    int numIterations = 200, numAnts = 15, ALPHA = 2, BETA = 1;
    double elapsedTime;
    Graph *graph = new Graph();
    csv::readNodes("real-graphs/graph1/nodes.csv", graph);
    csv::readEdges("real-graphs/graph1/edges.csv", graph);
    vector<vector<double>> distanceCache(graph->getNodes().size(), vector<double>(graph->getNodes().size(), -1));
    vector<vector<double>> pheromoneTrails(graph->getNodes().size(), vector<double>(graph->getNodes().size(), initialPheromones));
    Path bestPath = measureExecutionTime(elapsedTime, *graph, &Graph::performACO, pheromoneTrails, evaporationRate, pheromoneDeposit, numIterations, numAnts, ALPHA, BETA, distanceCache);
    file << "---------- Real graph1 ----------" << endl;
/*    double cost;
    vector<int> nodes = measureExecutionTime(elapsedTime, *graph, &Graph::approxTSPTour, cost);
    file << "Executing approxTSP" << endl
         << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
         << setw(30) << left << "Path:";
    for (int i = 0; i < nodes.size(); i++) {
        file << " " << nodes[i];
        if (i % 30 == 0 && i > 0 && i + 1 < nodes.size())
            file << endl << setw(30) << right << ' ';
    }
    file << endl << setw(30) << left << "Path total distance: " << cost
         << endl << endl;*/

    file << "Executing ACO with " << numAnts << " ants for " << numIterations << " iterations" << endl
         << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
         << setw(30) << left << "Path:";
    for (int i = 0; i < bestPath.nodes.size(); i++) {
        file << " " << bestPath.nodes[i];
        if (i % 30 == 0 && i > 0 && i + 1 < bestPath.nodes.size())
            file << endl << setw(30) << right << ' ';
    }
    file << endl << setw(30) << left << "Path total distance: " << bestPath.distance
         << endl << endl;

    double enhancement = measureExecutionTime(elapsedTime, *graph, &Graph::apply2OptSwap, bestPath, distanceCache, 20);
    file << "Executing 2-opt swap" << endl
         << setw(30) << left << "Elapsed time (ms): " << elapsedTime << endl
         << setw(30) << left << "Path after 2-opt:";
    for (int i = 0; i < bestPath.nodes.size(); i++) {
        file << " " << bestPath.nodes[i];
        if (i % 30 == 0 && i > 0 && i + 1 < bestPath.nodes.size())
            file << endl << setw(30) << right << ' ';
    }
    file << endl << setw(30) << left << "Path total distance: " << bestPath.distance << " (" << enhancement * 100 << "%)"
         << endl << endl;

    delete graph;
    return 0;
}