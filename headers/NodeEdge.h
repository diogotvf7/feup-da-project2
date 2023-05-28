//
// Created by Jaime on 28/05/2023.
//

#ifndef PROJETO_DA_NODEEDGE_H
#define PROJETO_DA_NODEEDGE_H
#include <iostream>
#include <vector>

class Edge;

class Node {
    int idNode;
    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    bool visited = false;
    std::string label;
public:
    Node(const int &idNode, const std::string &label = "");
    int getNodeId() const;
    Edge* addEdge(Node* dest,  int &edgeValue);
    std::vector<Edge*> getAdj() const;
    std::vector<Edge*> getIncoming() const;
};

class Edge {
    Node* src;
    Node* dest;
    int value;
public:
    Edge(Node* src, Node* dest, const int &value);
    int getValue() const;
};



#endif //PROJETO_DA_NODEEDGE_H
