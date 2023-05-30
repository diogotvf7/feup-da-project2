#include <iostream>
#include "headers/Graph.h"
#include "headers/csv.h"
#include <chrono>

using namespace std;
using namespace csv;

int main(){
    Graph *graph = new Graph();
    readEdges("toy-graphs/shipping.csv", graph);
    auto start = std::chrono::high_resolution_clock::now();
    vector<int>  test = graph->tspBacktracking();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    double executionTime = duration.count();

    // Print the execution time
    std::cout << "Execution time: " << executionTime << " ms" << std::endl;

    return 0;
}