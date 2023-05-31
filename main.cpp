#include <iostream>
#include "headers/Graph.h"
#include "headers/csv.h"
#include "headers/Menu.h"
#include <chrono>

int main(){
    Graph *graph = new Graph();
    readToyGraphs("stadiums.csv", graph);
    double cost = 0;
    double bestCost = INF;

    /*
    std::cout << "Ex1" << std::endl;
    auto start1 = std::chrono::high_resolution_clock::now();
    vector<int> ex1 = graph->tspBacktracking(bestCost);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration1 = end1 - start1;
    double execTime1 = duration1.count();
    std::cout << "Execution time: " << execTime1 << " ms" << std::endl;
    std::cout << "Cost: " << bestCost << std::endl;
    */

    std::cout << "Ex2" << std::endl;
    auto start2 = std::chrono::high_resolution_clock::now();
    vector<int> ex2 = graph->approxTSPTour(cost);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;
    double execTime2 = duration2.count();
    std::cout << "Execution time: " << execTime2 << " ms" << std::endl;
    std::cout << "Cost: " << cost << std::endl;
=======
int main() {
    std::vector<std::string> paths = {
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
    menu.init();



    return 0;
}