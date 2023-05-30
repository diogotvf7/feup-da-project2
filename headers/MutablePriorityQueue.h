#include <vector>
#include "NodeEdge.h"

#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)


class MutablePriorityQueue {
    std::vector<Node*> H;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, Node *x);

public:
    MutablePriorityQueue();
    void insert(Node *x);
    Node* extractMin();
    void decreaseKey(Node *x);
    bool empty();
};



