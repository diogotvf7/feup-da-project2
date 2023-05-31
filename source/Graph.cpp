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
void Graph::addEdge(const int &originNodeId, const int &destinyNodeId, double edgeValue) const {
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



vector<int> Graph::tspBacktracking(double &bestCost){
    vector<int> path;
    vector<int> bestPath;

    for(Node* node : nodes){
        node->setVisited(false);
    }

    //Node with id 0 is always our beginning and end
    Node* start = findNode(0);
    start->setVisited(true);
    path.push_back(0);

    backtrack(start, path, 0, bestPath, bestCost);
    bestPath.push_back(0);

    return bestPath;
}

void Graph::backtrack(Node* currentNode, std::vector<int> &path, double currentCost, std::vector<int> &bestPath, double &bestCost){

    bool allNodesVisited = true;
    for(Node* node : nodes){
        if(!node->isVisited()) {allNodesVisited = false; break;}
    }
    if(allNodesVisited && connectedToStart(currentNode)){
        if((currentCost + getEdgeWeightFromTwoNodes(currentNode, findNode(0)) ) < bestCost){
            bestPath = path;
            bestCost = currentCost + getEdgeWeightFromTwoNodes(currentNode, findNode(0));
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


void Graph::prim() {
    vector<Edge*> res;
    if(nodes.empty()) return;

    for(Node* node : nodes){
        node->setDist(INF);
        node->setPath(nullptr);
        node->setVisited(false);
    }

    Node* s = findNode(0);
    s->setDist(0);

    MutablePriorityQueue q;
    q.insert(s);

    while(!q.empty()){
        Node* v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()){
            Node* w = e->getDest();
            if(!w->isVisited()){
                auto oldDistance = w->getDist();
                if(e->getValue() < oldDistance){
                    w->setDist(e->getValue());
                    w->setPath(e);
                    if(oldDistance == INF){
                        q.insert(w);
                    }
                    else{
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

}

std::vector<Edge*> Graph::sortMinWeight(std::vector<Edge*> v){
    return v;
}


void Graph::preOrderWalk(Node* node, std::vector<int>& tour, double &cost) {
    node->setVisited(true);
    for (Edge* edge : node->getAdj()) {
        Node* neighbor = edge->getDest();
        if(neighbor->getPath() != nullptr){ //
            if(neighbor->getPath()->getSrc() == node){
                tour.push_back(neighbor->getNodeId());
                preOrderWalk(neighbor, tour, cost);
            }
        }
    }
}

vector<int> Graph::approxTSPTour(double &cost){
    vector<int> tour;
    this->prim();
    for(Node* node : nodes) node->setVisited(false);

    tour.push_back(0);
    preOrderWalk(findNode(0), tour, cost);
    tour.push_back(0);

    for(int i = 0; i < (tour.size() - 1); i++){
        cost += getEdgeWeightFromTwoNodes(findNode(tour[i]), findNode(tour[i + 1]));
    }
    return tour;
}







