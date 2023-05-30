#include <algorithm>
#include "../headers/Graph.h"

using namespace std;

Node* Graph::findNode(const int& idNode) const {
    auto it = nodes.find(idNode);
    return it == nodes.end() ? nullptr : it->second;
}

void Graph::addNode(Node *node) {
    nodes.emplace(node->getId(), node);
}

node_map Graph::getNodes() const {
    return nodes;
}

void Graph::createEdge(const int &src, const int &dest, int dist) const {
    Node* origin = findNode(src);
    Node* destiny = findNode(dest);
    if (origin == nullptr || destiny == nullptr) return;
    origin->insertEdge(destiny, dist);
    destiny->insertEdge(origin, dist);
}

void Graph::resetGraph() {
    for (const auto& node : nodes) {
        node.second->setVisited(false);
    }
}

vector<int> Graph::tspBacktracking() {
    vector<int> path;
    vector<int> bestPath;
    double bestCost = INF;

    resetGraph();

    //Node with id 0 is always our beginning and end
    Node* start = findNode(0);
    start->setVisited(true);
    path.push_back(start->getId());

    backtrack(start, path, 0, bestPath, bestCost);
    bestPath.push_back(0);

    return bestPath;
}

void Graph::backtrack(Node* currentNode, std::vector<int> &path, double currentCost, std::vector<int> &bestPath, double &bestCost) {
    bool allNodesVisited = true;
    for (const auto& node : nodes) {
        if (!node.second->isVisited()) {
            allNodesVisited = false;
            break;
        }
    }

    if (allNodesVisited && currentNode->connectedTo(0)) {
        Edge *e = currentNode->getEdge(0);
        double dist = e ? e->getDist() : 0;
        if ((currentCost + dist) < bestCost) {
            bestPath = path;
            bestCost = currentCost;
        }
    }

    for (Edge* edge : currentNode->getAdj()) {
        Node* adjNode = edge->getDest();
        if (!adjNode->isVisited()) {
            adjNode->setVisited(true);
            path.push_back(adjNode->getId());
            backtrack(adjNode, path,currentCost + edge->getDist(), bestPath, bestCost);
            adjNode->setVisited(false);
            path.pop_back();
        }
    }
}


