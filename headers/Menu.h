#ifndef PROJETO_DA_MENU_H
#define PROJETO_DA_MENU_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include "Graph.h"
#include "csv.h"

class Menu {
    std::string input;
    std::unordered_map<std::string,Graph*> graphs;
    std::vector<std::string> cachedGraphs;
    std::vector<std::string> headers;
    std::string func;
    std::string arg;
public:
    explicit Menu(const std::vector<std::string> &paths);
    void readGraph(const std::string &path);
    void updateCache(const std::string& path);

    void init();
    bool selectGraph(int headerIdx);
    bool displayInfo(int headerIdx, const std::string &path);
    void chooseACOParams(double &initialPheromones, double &evaporationRate, double &pheromoneDeposit,
                         int &numIterations, int &numAnts, int &ALPHA, int &BETA);
    bool displayPath(const Path &path, const std::string &graphPath, int headerIdx);

    std::string static center(const std::string &str, int width);
    void static cleanTerminal();
};


#endif //PROJETO_DA_MENU_H
