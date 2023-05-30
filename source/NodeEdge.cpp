//
// Created by Jaime on 28/05/2023.
//

#include "../headers/NodeEdge.h"


using namespace std;

Edge::Edge(Node* src, Node* dest, const double &value) {
    this->src = src;
    this->dest = dest;
    this->value = value;
}

double Edge::getValue() const {return value;}

Node* Edge::getSrc() const {return src;}

Node* Edge::getDest() const {return dest;}

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

Edge* Node::addEdge(Node* dest, double &edgeValue) {
    Edge* newEdge = new Edge(this, dest, edgeValue);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);

    return newEdge;
}

void Node::setVisited(bool status) {
    this->visited = status;
}

bool Node::isVisited() const {
    return visited;
}

int Node::getQueueIndex() const {
    return queueIndex;
}

Edge* Node::getPath() const {return path;}

double Node::getDist() const {return dist;}

void Node::setQueueIndex(int newQueueIndex) {
    this->queueIndex = newQueueIndex;
}

void Node::setDist(int distance) {this->dist = distance;}

void Node::setPath(Edge *newPath) {this->path = newPath;}

bool Node::operator<(Node & node) const {
    return this->dist < node.dist;
}
