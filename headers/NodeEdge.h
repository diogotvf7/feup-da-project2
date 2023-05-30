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

    int queueIndex = 0;
    double dist = 0;

    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    bool visited = false;
    Edge* path = nullptr; //needed for prim's algorithm
    std::string label;
public:
    Node(const int &idNode, const std::string &label = "");
    bool operator<(Node & node) const;

    Edge* addEdge(Node* dest,  double &edgeValue);

    bool isVisited() const;
    std::vector<Edge*> getAdj() const;
    std::vector<Edge*> getIncoming() const;
    int getNodeId() const;
    int getQueueIndex() const;
    Edge* getPath() const;
    double getDist() const;

    void setPath(Edge* newPath);
    void setQueueIndex(int queueIndex);
    void setVisited(bool status);
    void setDist(int distance);
};

class Edge {
    Node* src;
    Node* dest;
    double value;
public:
    Edge(Node* src, Node* dest, const double &value);
    double getValue() const;
    Node* getSrc() const;
    Node* getDest() const;
};



#endif //PROJETO_DA_NODEEDGE_H
