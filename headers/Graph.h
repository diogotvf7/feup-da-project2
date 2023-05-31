#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "NodeEdge.h"
#include "MutablePriorityQueue.h"

#define INF INT16_MAX
#define node_map std::unordered_map<int, Node*>

class Graph {
    node_map nodes;

public:
    Node *findNode(const int &idNode) const;
    void addNode(Node *node);
    node_map getNodes() const;
    void createEdge(const int &src, const int &dest, double dist) const;

    /*First Exercise*/
    std::vector<int> tspBacktracking(double &bestCost);
    void backtrack(Node *currentNode, std::vector<int> &path, double currentCost, std::vector<int> &bestPath, double &bestCost);

    /*Second Exercise*/
    void prim();
    void preOrderWalk(Node *node, std::vector<int> &tour);
    std::vector<int> approxTSPTour(double &cost);
};

template<typename Func, typename Object, typename... Args>
auto measureExecutionTime(double &elapsedTime, Object&& object, Func&& func, Args&&... args)
{
 /*   auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Start: " << start.time_since_epoch().count() << std::endl;

    auto result = (std::forward<Object>(object).*std::forward<Func>(func))(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "End: " << end.time_since_epoch().count() << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Duration: " << duration.count() << " ms" << std::endl;

    elapsedTime = duration.count();

    return result;*/

    auto start = std::chrono::high_resolution_clock::now();

    auto result = (std::forward<Object>(object).*std::forward<Func>(func))(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    elapsedTime = duration.count();

    return result;
}

#endif //GRAPH_H
