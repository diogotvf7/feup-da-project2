#ifndef GRAPH_H
#define GRAPH_H

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
    std::vector<Edge*> prim();
    void preOrderWalk(Node *node, std::vector<int> &tour, double &cost);
    std::vector<int> approxTSPTour(double &cost);
};

#endif //GRAPH_H
