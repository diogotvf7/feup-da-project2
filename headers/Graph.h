//
// Created by Jaime on 27/05/2023.
//

#ifndef PROJETO_DA_GRAPH_H
#define PROJETO_DA_GRAPH_H

#include <vector>
#include "NodeEdge.h"
#define INF INT16_MAX

class Graph {
    std::vector<Node*> nodes;
public:
    Node* findNode(const int &idNode) const;
    void addNode(Node* node);
    void removeNode(const int &idNode);
    std::vector<Node*> getNodes() const;
    bool connectedToStart(Node* currentNode);
    int getEdgeWeightFromTwoNodes(Node* node1, Node* node2);
    void addEdge(const int &originNodeId, const int &destinyNodeId,  int edgeValue) const;

    /*First Exercise*/
    std::vector<int> tspBacktracking();
    void backtrack(Node* currentNode, std::vector<int> &path, int currentCost, std::vector<int> &bestPath, int &bestCost);
};


#endif //PROJETO_DA_GRAPH_H
