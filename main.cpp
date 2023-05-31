#include <iostream>
#include "headers/Graph.h"
#include "headers/Utils.h"
#include <chrono>
using namespace std;
using namespace utils;

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


}