#ifndef NODE_EDGE_H
#define NODE_EDGE_H

#include <iostream>
#include <vector>
#include "Coordinate.h"

class Edge;

/*                                     Node                                      */
class Node {
    int id;
    Coordinate coord;
    std::string label;

    int queueIndex = 0;
    double dist = 0;
    Edge* path = nullptr; //needed for prim's algorithm
    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    bool visited = false;

public:
    explicit Node(const int &id);
    explicit Node(const int &id, Coordinate coord);
    explicit Node(const int &id, const std::string &label);

    [[nodiscard]] int getId() const;
    [[nodiscard]] bool isVisited() const;
    [[nodiscard]] double getDist() const;
    [[nodiscard]] int getQueueIndex() const;
    [[nodiscard]] Edge *getPath() const;
    [[nodiscard]] Coordinate getCoord() const;
    [[nodiscard]] Edge *getEdge(int dest) const;
    [[nodiscard]] std::vector<Edge*> getAdj() const;
    [[nodiscard]] std::vector<Edge*> getIncoming() const;
    void setVisited(bool status);
    void setDist(double distance);
    void setQueueIndex(int queueIndex);
    void setPath(Edge *newPath);
    void setCoord(Coordinate _coord);
    Edge* insertEdge(Node *dest, double &distance);
    [[nodiscard]] bool connectedTo(int id) const;
    bool operator<(Node &node) const;
};

/*                                     Edge                                      */
class Edge {
    Node *src;
    Node *dest;
    double dist;
    double pheromone;
    Coordinate coord;

public:
    Edge(Node *src, Node *dest, const double &dist);
    [[nodiscard]] double getDist() const;
    [[nodiscard]] Node *getSrc() const;
    [[nodiscard]] Node *getDest() const;
};

#endif //NODE_EDGE_H
