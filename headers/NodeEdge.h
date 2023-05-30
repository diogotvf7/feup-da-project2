#ifndef PROJETO_DA_NODEEDGE_H
#define PROJETO_DA_NODEEDGE_H

#include <iostream>
#include <vector>
#include "Coordinate.h"

class Edge;

class Node {
    int id;
    Coordinate coord;
    std::string label;

    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    bool visited = false;

public:
    explicit Node(const int &id);
    explicit Node(const int &id, Coordinate coord);
    explicit Node(const int &id, const std::string &label);
    int getId() const;
    Edge* insertEdge(Node* dest, int &edgeValue);
    std::vector<Edge*> getAdj() const;
    std::vector<Edge*> getIncoming() const;
    void setVisited(bool status);
    bool isVisited() const;
    Edge *getEdge(int dest) const;
    bool connectedTo(int id) const;
};

class Edge {
    Node* src;
    Node* dest;
    double dist;

public:
    Edge(Node* src, Node* dest, const double &dist);
    double getDist() const;
    Node* getSrc() const;
    Node* getDest() const;
};

#endif //PROJETO_DA_NODEEDGE_H
