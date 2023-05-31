#include <iostream>
#include "headers/Graph.h"
#include "headers/csv.h"
#include "headers/Menu.h"
#include <chrono>

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
            "real-graphs/graph1",
            "real-graphs/graph2",
            "real-graphs/graph3",
            };
    Menu menu = Menu(paths);
    menu.init();
    

    return 0;
}