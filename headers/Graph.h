//
// Created by Jaime on 27/05/2023.
//

#ifndef PROJETO_DA_GRAPH_H
#define PROJETO_DA_GRAPH_H

#include <vector>
#include "NodeEdge.h"


class Graph {
    std::vector<Node*> nodes;
public:
    Node* findNode(const int &idNode) const;
    void addNode(Node* node);
    void removeNode(const int &idNode);
    std::vector<Node*> getNodes() const;
    void addEdge(const int &originNodeId, const int &destinyNodeId,  int edgeValue);
};


#endif //PROJETO_DA_GRAPH_H
