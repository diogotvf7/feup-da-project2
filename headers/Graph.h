//
// Created by Jaime on 27/05/2023.
//

#ifndef PROJETO_DA_GRAPH_H
#define PROJETO_DA_GRAPH_H

#include <vector>
#include "MutablePriorityQueue.h"
#define INF INT16_MAX

class Graph {
    std::vector<Node*> nodes;
public:
    Node* findNode(const int &idNode) const;
    void addNode(Node* node);


    bool connectedToStart(Node* currentNode);
    int getEdgeWeightFromTwoNodes(Node* node1, Node* node2);
    void addEdge(const int &originNodeId, const int &destinyNodeId,  double edgeValue) const;

    /*First Exercise*/
    std::vector<int> tspBacktracking(double &bestCost);
    void backtrack(Node* currentNode, std::vector<int> &path, double currentCost, std::vector<int> &bestPath, double &bestCost);

    /*Second Exercise*/
    void prim();
    void preOrderWalk(Node* node, std::vector<int>& tour, double &cost);
    std::vector<int> approxTSPTour(double &cost);
    std::vector<Edge*> sortMinWeight(std::vector<Edge*> v);

};


#endif //PROJETO_DA_GRAPH_H
