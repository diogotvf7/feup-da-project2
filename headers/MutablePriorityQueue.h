#include <vector>
#include "NodeEdge.h"

#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)


class MutablePriorityQueue {
    std::vector<Node*> H;
    /**
     * @brief Function for heapifying up
     * @param i the index of the node we want to heapify up
     */
    void heapifyUp(unsigned i);
    /**
     * @brief Function for heapifying down
     * @param i the index of the node we want to heapify down
     */
    void heapifyDown(unsigned i);
    /**
     * @brief Function for setting a node in the priority queue
     * @param i the index of the node we want to set
     * @param x the node we want to set
     */
    inline void set(unsigned i, Node* x);

public:
    /**
     * @brief Constructor for the MutablePriorityQueue class
     */
    MutablePriorityQueue();
    /**
     * @brief Function for inserting a node into the priority queue
     * @param x the node we want to insert
     */
    void insert(Node* x);
    /**
     * @brief Function for removing the minimum node from the priority queue
     * @return returns the minimum node
     */
    Node* extractMin();
    /**
     * @brief Function for removing a node from the priority queue
     * @param x the node we want to remove
     */
    void decreaseKey(Node* x);
    /**
     * @brief Function for checking if the priority queue is empty
     * @return returns true if the priority queue is empty, false otherwise
     */
    bool empty();
};



