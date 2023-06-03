//
// Created by Jaime on 29/05/2023.
//

#include "../headers/MutablePriorityQueue.h"

MutablePriorityQueue::MutablePriorityQueue() {
    H.push_back(nullptr);
}

bool MutablePriorityQueue::empty() {
    return H.size() == 1;
}

Node* MutablePriorityQueue::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if(H.size() > 1) heapifyDown(1);
    x->setQueueIndex(0);
    return x;
}

void MutablePriorityQueue::insert(Node *x) {
    H.push_back(x);
    heapifyUp(H.size()-1);
}

void MutablePriorityQueue::decreaseKey(Node *x) {
    heapifyUp(x->getQueueIndex());
}

void MutablePriorityQueue::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

void MutablePriorityQueue::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k+1 < H.size() && *H[k+1] < *H[k])
            ++k; // right child of i
        if ( ! (*H[k] < *x) )
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

void MutablePriorityQueue::set(unsigned i, Node *x) {
    H[i] = x;
    x->setQueueIndex(i);
}