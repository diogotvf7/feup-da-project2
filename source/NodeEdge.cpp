#include "../headers/NodeEdge.h"

using namespace std;

Edge::Edge(Node* src, Node* dest, const double &dist) {
    this->src = src;
    this->dest = dest;
    this->dist = dist;
}

double Edge::getDist() const {return dist;}

Node* Edge::getSrc() const {return src;}

Node* Edge::getDest() const {return dest;}

Node::Node(const int &id) {
    this->id = id;
    this->coord = Coordinate();
    this->label = "";
}

Node::Node(const int &id, Coordinate coord) {
    this->id = id;
    this->coord = coord;
    this->label = "";
}

Node::Node(const int &id, const std::string &label) {
    this->id = id;
    this->coord = Coordinate();
    this->label = label;
}

int Node::getId() const {
    return id;
}

std::vector<Edge*> Node::getAdj() const {
    return adj;
}

std::vector<Edge*> Node::getIncoming() const {
    return incoming;
}

Edge* Node::insertEdge(Node* dest, int &dist) {
    Edge* e = new Edge(this, dest, dist);
    adj.push_back(e);
    dest->incoming.push_back(e);

    return e;
}

void Node::setVisited(bool status) {
    this->visited = status;
}

bool Node::isVisited() const {
    return visited;
}

bool Node::connectedTo(int dest) const {
    return getEdge(dest) != nullptr;
}

Edge *Node::getEdge(int dest) const {
    for (Edge* edge : adj)
        if (edge->getDest()->getId() == dest)
            return edge;
    return nullptr;
}
