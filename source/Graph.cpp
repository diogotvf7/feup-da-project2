//
// Created by Jaime on 27/05/2023.
//

#include "../headers/Graph.h"
using namespace std;

Node* Graph::findNode(const int &idNode) const {
    for(Node* node : nodes){
        if(node->getNodeId() == idNode)
            return node;
    }
    return nullptr;
}

void Graph::addNode(Node *node) {
    if(findNode(node->getNodeId()) == nullptr)
        nodes.push_back(node);
}

//to be finished
void Graph::addEdge(const int &originNodeId, const int &destinyNodeId, int edgeValue) {
    Node* origin = findNode(originNodeId);
    Node* destiny = findNode(destinyNodeId);
    if(origin == nullptr || destiny == nullptr) return;
    Edge* edge1 = origin->addEdge(destiny, edgeValue);
    Edge* edge2 = destiny->addEdge(origin, edgeValue);
}

vector<Node*> Graph::getNodes() const {
    return nodes;
}


