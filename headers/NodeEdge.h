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
    /**
     * @brief Node constructor
     * @param id the id of the node
     */
    explicit Node(const int &id);
    /**
     * @brief Node constructor
     * @param id the id of the node
     * @param coord the coordinates of the node
     */
    explicit Node(const int &id, Coordinate coord);
    /**
     * @brief Node constructor
     * @param id the id of the node
     * @param label the label of the node
     */
    explicit Node(const int &id, const std::string &label);
    /**
     * @brief Get function for the id of the node
     * @return the id of the node
     */
    [[nodiscard]] int getId() const;
    /**
     * @brief Get function for the visited state of the node
     * @return the visited state of the node
     */
    [[nodiscard]] bool isVisited() const;
    /**
     * @brief Get function for the distance of the node
     * @return the distance of the node
     */
    [[nodiscard]] double getDist() const;
    /**
     * @brief Get function for the queue index of the node
     * @return the queue index of the node
     */
    [[nodiscard]] int getQueueIndex() const;
    /**
     * @brief Get function for the path of the node
     * @return the path of the node
     */
    [[nodiscard]] Edge *getPath() const;
    /**
     * @brief Get function for the coordinates of the node
     * @return the coordinates of the node
     */
    [[nodiscard]] Coordinate getCoord() const;
    /**
     * @brief This function tries to find an edge connecting the node to another node
     * @return returns a pointer to the edge connecting the node to the other node, or nullptr if no such edge exists
     */
    [[nodiscard]] Edge *getEdge(int dest) const;
    /**
     * @brief Get function for the adjacency table of the node
     * @return the adjacency table of the node
     */
    [[nodiscard]] std::vector<Edge*> getAdj() const;
    /**
     * @brief Set function for the visited state of the node
     * @param status the new visited state of the node
     */
    void setVisited(bool status);
    /**
     * @brief Set function for the distance of the node
     * @param distance the new distance of the node
     */
    void setDist(double distance);
    /**
     * @brief Set function for the queue index of the node
     * @param queueIndex the new queue index of the node
     */
    void setQueueIndex(int queueIndex);
    /**
     * @brief Set function for the path of the node
     * @param newPath the new path of the node
     */
    void setPath(Edge *newPath);
    /**
     * @brief Function to insert an edge between this node and dest
     * @param dest the node that will be connected to this node
     * @param distance the distance between the two nodes
     * @return returns a pointer to the created edge
     */
    Edge* insertEdge(Node *dest, double &distance);
    /**
     * @brief Function that informs if the node is connected to another node
     * @param id the id of the node we want to check if this node is connected to
     * @return returns true if the node is connected to the node with the given id, false otherwise
     */
    [[nodiscard]] bool connectedTo(int id) const;
    /**
     * @brief Overload of the < operator for the Node class
     * @param node the node to which we want to compare this node
     * @return returns true if this node has a lower dist value than the other node, false otherwise
     */
    bool operator<(Node &node) const;
};

/*                                     Edge                                      */
class Edge {
    Node *src;
    Node *dest;
    double dist;
    double pheromone;

public:
    /**
     * @brief Edge constructor
     * @param src the source node of the edge
     * @param dest the destination node of the edge
     * @param dist the distance between the two nodes
     */
    Edge(Node *src, Node *dest, const double &dist);
    /**
     * @brief Get function for the distance of the edge
     * @return the distance of the edge
     */
    [[nodiscard]] double getDist() const;
    /**
     * @brief Get function for the source node of the edge
     * @return the source node of the edge
     */
    [[nodiscard]] Node *getSrc() const;
    /**
     * @brief Get function for the destination node of the edge
     * @return the destination node of the edge
     */
    [[nodiscard]] Node *getDest() const;
    /**
     * @brief Get function for the amount of pheromones in the edge
     * @return the amount of pheromones in the edge
     */
    [[nodiscard]] double getPheromone() const;
    /**
     * @brief Set function for the amount of pheromones in the edge
     * @param _pheromone the new amount of pheromones in the edge
     */
    void setPheromone(double _pheromone);
};

#endif //NODE_EDGE_H
