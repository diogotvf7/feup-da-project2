#include <iostream>
#include "headers/Graph.h"
#include "headers/Utils.h"
using namespace std;
using namespace utils;

int main(){
    Graph *graph = new Graph();
    readToyGraphs("tourism.csv", graph);
    cout << "hello world";
}