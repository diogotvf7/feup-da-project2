//
// Created by Jaime on 28/05/2023.
//

#include "../headers/NodeEdge.h"


using namespace std;

Edge::Edge(Node* src, Node* dest, const int &value) {
    this->src = src;
    this->dest = dest;
    this->value = value;
}

int Edge::getValue() const {return value;}


Node::Node(const int &idNode, const string &label) {
    this->idNode = idNode;
    this->label = label;
}

int Node::getNodeId() const {
    return idNode;
}

std::vector<Edge*> Node::getAdj() const {
    return adj;
}

std::vector<Edge*> Node::getIncoming() const {
    return incoming;
}

Edge* Node::addEdge(Node* dest, int &edgeValue) {
    Edge* newEdge = new Edge(this, dest, edgeValue);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);

    return newEdge;
}
