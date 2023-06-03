#ifndef GRAPH_H
#define GRAPH_H

#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cfloat>
#include "NodeEdge.h"
#include "MutablePriorityQueue.h"


#include <fstream>


#define INF INT32_MAX
#define node_map std::unordered_map<int, Node*>

struct AntPath {
    std::vector<int> path;
    double distance;
};

class Graph {
    node_map nodes;

public:
    Node *findNode(const int &idNode) const;
    void addNode(Node *node);
    node_map getNodes() const;
    void createEdge(const int &src, const int &dest, double dist) const;
    double distanceBetween(int src, int dest, std::vector<std::vector<double>> &cache);

    /*First Exercise*/
    std::vector<int> tspBacktracking(double &bestCost);
    void backtrack(Node *currentNode, std::vector<int> &path, double currentCost, std::vector<int> &bestPath, double &bestCost);

    /*Second Exercise*/
    void prim();
    void preOrderWalk(Node *node, std::vector<int> &tour);
    std::vector<int> approxTSPTour(double &cost);

    /*Third Exercise*/
    // Function to update pheromone trails based on ant paths
    static void updatePheromoneTrails(std::vector<std::vector<double>>& pheromoneTrails,
                                      const std::vector<AntPath> &ants,
                                      double evaporationRate, double pheromoneDeposit);

    // Function to perform ACO with two ants in the same thread
    AntPath performACO(std::vector<std::vector<double>> &pheromoneTrails,
                           double evaporationRate, double pheromoneDeposit,
                           int numIterations, int numAnts, int ALPHA, int BETA,
                           std::vector<std::vector<double>> &distanceCache);

    int getRandomStartNode() const;

    void apply2OptSwap(AntPath& antPath, std::vector<std::vector<double>> &distanceCache);
};

/*                           Performance analysis                           */

template<typename Func, typename Object, typename... Args>
auto measureExecutionTime(double &elapsedTime, Object&& object, Func&& func, Args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();

    auto result = (std::forward<Object>(object).*std::forward<Func>(func))(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    elapsedTime = duration.count();

    return result;
}

#endif //GRAPH_H
