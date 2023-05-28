#include <iostream>
#include "headers/Graph.h"
#include "headers/Utils.h"
#include <chrono>
using namespace std;
using namespace utils;

int main(){
    Graph *graph = new Graph();
    readToyGraphs("shipping.csv", graph);
    auto start = std::chrono::high_resolution_clock::now();
    vector<int>  test = graph->tspBacktracking();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    double executionTime = duration.count();

    // Print the execution time
    std::cout << "Execution time: " << executionTime << " ms" << std::endl;
}