//
// Created by Jaime on 27/05/2023.
//

#include <algorithm>
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
void Graph::addEdge(const int &originNodeId, const int &destinyNodeId, int edgeValue) const {
    Node* origin = findNode(originNodeId);
    Node* destiny = findNode(destinyNodeId);
    if(origin == nullptr || destiny == nullptr) return;
    origin->addEdge(destiny, edgeValue);
    destiny->addEdge(origin, edgeValue);
}

bool Graph::connectedToStart(Node *currentNode) {
    for(Edge* edge : currentNode->getAdj()){
        if(edge->getDest()->getNodeId() == 0) return true;
    }
    return false;
}


int Graph::getEdgeWeightFromTwoNodes(Node* node1, Node* node2){
    for(Edge* edge : node1->getAdj()){
        if(edge->getDest()->getNodeId() == node2->getNodeId()){
            return edge->getValue();
        }
    }
    return 0;
}

vector<Node*> Graph::getNodes() const {
    return nodes;
}

vector<int> Graph::tspBacktracking(){
    vector<int> path;
    vector<int> bestPath;
    int bestCost = INF;

    for(Node* node : nodes){
        node->setVisited(false);
    }

    //Node with id 0 is always our beginning and end
    Node* start = findNode(0);
    start->setVisited(true);
    path.push_back(start->getNodeId());

    backtrack(start, path, 0, bestPath, bestCost);
    bestPath.push_back(0);

    return bestPath;
}

void Graph::backtrack(Node* currentNode, std::vector<int> &path, int currentCost, std::vector<int> &bestPath, int &bestCost){

    bool allNodesVisited = true;
    for(Node* node : nodes){
        if(!node->isVisited()) {allNodesVisited = false; break;}
    }
    if(allNodesVisited && connectedToStart(currentNode)){
        if((currentCost + getEdgeWeightFromTwoNodes(currentNode, findNode(0)) ) < bestCost){
            bestPath = path;
            bestCost = currentCost;
        }
    }

    for(Edge* edge : currentNode->getAdj()){
        Node* adjNode = edge->getDest();
        if(!adjNode->isVisited()){
            adjNode->setVisited(true);
            path.push_back(adjNode->getNodeId());
            backtrack(adjNode, path,currentCost + edge->getValue(), bestPath, bestCost);
            adjNode->setVisited(false);
            path.pop_back();
        }
    }
}


