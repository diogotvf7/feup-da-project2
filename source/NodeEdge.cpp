#include "../headers/NodeEdge.h"

using namespace std;

/*                              Node                              */

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

bool Node::isVisited() const {
    return visited;
}

double Node::getDist() const {
    return dist;
}

int Node::getQueueIndex() const {
    return queueIndex;
}

Edge* Node::getPath() const {
    return path;
}

Edge *Node::getEdge(int dest) const {
    for (Edge *edge: adj)
        if (edge->getDest()->getId() == dest)
            return edge;
    return nullptr;
}

std::vector<Edge*> Node::getAdj() const {
    return adj;
}

std::vector<Edge*> Node::getIncoming() const {
    return incoming;
}

void Node::setVisited(bool status) {
    this->visited = status;
}

void Node::setDist(double distance) {
    this->dist = distance;
}

void Node::setQueueIndex(int newQueueIndex) {
    this->queueIndex = newQueueIndex;
}

void Node::setPath(Edge *newPath) {
    this->path = newPath;
}

Edge* Node::insertEdge(Node* dest, double &distance) {
    Edge* e = new Edge(this, dest, distance);
    adj.push_back(e);
    dest->incoming.push_back(e);

    return e;
}

bool Node::connectedTo(int dest) const {
    return getEdge(dest) != nullptr;
}

bool Node::operator<(Node & node) const {
    return this->dist < node.dist;
}

/*                              Edge                              */

Edge::Edge(Node* src, Node* dest, const double &dist) {
    this->src = src;
    this->dest = dest;
    this->dist = dist;
}

double Edge::getDist() const {
    return dist;
}

Node* Edge::getSrc() const {
    return src;
}

Node* Edge::getDest() const {
    return dest;
}