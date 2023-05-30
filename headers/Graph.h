#ifndef PROJETO_DA_GRAPH_H
#define PROJETO_DA_GRAPH_H

#include <vector>
#include <unordered_map>
#include "NodeEdge.h"

#define INF INT16_MAX
#define node_map std::unordered_map<int, Node*>

class Graph {
    node_map nodes;

public:
    Node* findNode(const int &idNode) const;
    void addNode(Node* node);
    node_map getNodes() const;
    void createEdge(const int &src, const int &dest, int dist) const;
    void resetGraph();

    /*First Exercise*/
    std::vector<int> tspBacktracking();
    void backtrack(Node* currentNode, std::vector<int> &path, double currentCost, std::vector<int> &bestPath, double &bestCost);
};

#endif //PROJETO_DA_GRAPH_H
