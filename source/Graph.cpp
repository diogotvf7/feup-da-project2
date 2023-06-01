#include <algorithm>
#include "../headers/Graph.h"

using namespace std;

Node *Graph::findNode(const int &idNode) const {
    auto it = nodes.find(idNode);
    return it == nodes.end() ? nullptr : it->second;
}

void Graph::addNode(Node *node) {
    nodes.emplace(node->getId(), node);
}

node_map Graph::getNodes() const {
    return nodes;
}

void Graph::createEdge(const int &src, const int &dest, double dist) const {
    Node *origin = findNode(src);
    Node *destiny = findNode(dest);
    if (origin == nullptr || destiny == nullptr) return;
    origin->insertEdge(destiny, dist);
    destiny->insertEdge(origin, dist);
}

vector<int> Graph::tspBacktracking(double &bestCost) {
    vector<int> path;
    vector<int> bestPath;

    for (const auto &[key, node]: nodes) {
        node->setVisited(false);
    }

    //Node with id 0 is always our beginning and end
    Node *start = findNode(0);
    start->setVisited(true);
    path.push_back(start->getId());

    backtrack(start, path, 0, bestPath, bestCost);
    bestPath.push_back(0);

    return bestPath;
}

void Graph::backtrack(Node *currentNode, vector<int> &path, double currentCost, vector<int> &bestPath, double &bestCost) {
    bool allNodesVisited = true;
    for (const auto &[key, node] : nodes) {
        if (!node->isVisited()) {
            allNodesVisited = false;
            break;
        }
    }

    if (allNodesVisited && currentNode->connectedTo(0)) {
        Edge *e = currentNode->getEdge(0);
        double dist = e->getDist();
        if ((currentCost + dist) < bestCost) {
            bestPath = path;
            bestCost = currentCost + dist;
        }
    }

    for (Edge *edge : currentNode->getAdj()) {
        Node *adjNode = edge->getDest();
        if (adjNode->isVisited()) continue;
        adjNode->setVisited(true);
        path.push_back(adjNode->getId());
        backtrack(adjNode, path,currentCost + edge->getDist(), bestPath, bestCost);
        adjNode->setVisited(false);
        path.pop_back();
    }
}

void Graph::prim() {
    vector<Edge*> res;
    if (nodes.empty()) return;

    for (const auto &[key, node] : nodes) {
        node->setDist(INF);
        node->setPath(nullptr);
        node->setVisited(false);
    }

    Node *s = findNode(0);
    s->setDist(0);

    MutablePriorityQueue q;
    q.insert(s);

    while (!q.empty()) {
        Node *v = q.extractMin();
        v->setVisited(true);
        for (auto &e : v->getAdj()) {
            Node *w = e->getDest();
            if (w->isVisited()) continue;
            auto oldDistance = w->getDist();
            if (e->getDist() < oldDistance) {
                w->setDist(e->getDist());
                w->setPath(e);
                if (oldDistance == INF) q.insert(w);
                else q.decreaseKey(w);
            }
        }
    }
}

void Graph::preOrderWalk(Node *node, vector<int> &tour) {
    node->setVisited(true);
    for (Edge *edge : node->getAdj()) {
        Node *dest = edge->getDest();
        if (dest->getPath() == nullptr) continue;
        if (dest->getPath()->getSrc() == node) {
            tour.push_back(dest->getId());
            preOrderWalk(dest, tour);
        }
    }
}

vector<int> Graph::approxTSPTour(double &cost) {
    vector<int> tour;
    prim();
    for (const auto &[key, node] : nodes)
        node->setVisited(false);

    tour.push_back(0);
    preOrderWalk(findNode(0), tour);
    tour.push_back(0);

    for (int i = 0; i < (tour.size() - 1); i++)
        cost += findNode(tour[i])->getEdge(tour[i + 1])->getDist();

    return tour;
}

void Graph::updatePheromoneTrails(vector<vector<double>> &pheromoneTrails, const vector<AntPath> &ants,
                                         double evaporationRate, double pheromoneDeposit) {
    // Evaporate pheromone trails
    for (auto &trailRow : pheromoneTrails)
        for (auto &trail : trailRow)
            trail *= (1.0 - evaporationRate);

    for (const auto &ant : ants) {
        double pheromoneAddition = pheromoneDeposit / ant.distance;
        for (size_t i = 0; i < ant.path.size() - 1; ++i) {
            int src = ant.path[i];
            int dest = ant.path[i + 1];
            pheromoneTrails[src][dest] += pheromoneAddition;
            pheromoneTrails[dest][src] += pheromoneAddition;
        }
    }
}

void Graph::performACO(vector<vector<double>> &pheromoneTrails, double evaporationRate, double pheromoneDeposit,
                       int numIterations, int numAnts, int ALPHA, int BETA) {
    random_device rd;
    mt19937 rng(rd());
    uniform_real_distribution<double> distribution(0.0, 1.0);

    vector<AntPath> ants;
    AntPath bestAntPath;

    for (int iteration = 0; iteration < numIterations; ++iteration) {

        // Construct ant paths          vv
        for (int ant = 0; ant < numAnts; ++ant) {
            // Construct path for ant
            AntPath antPath = {{0}, 0};
            for (auto &[key, node] : nodes)
                node->setVisited(false);
            int currentNode = 0;
            nodes[currentNode]->setVisited(true);
            for (int i = 0; i < nodes.size() - 1; ++i) {
                // Select next node
                double sum = 0.0;
                for (int j = 0; j < nodes.size(); ++j) {
                    if (!nodes[j]->isVisited()) {
                        double dist = nodes[currentNode]->getEdge(j)
                                ? nodes[currentNode]->getEdge(j)->getDist()
                                : nodes[currentNode]->getCoord().distanceTo(nodes[j]->getCoord());
                        sum += pow(pheromoneTrails[currentNode][j], ALPHA) *
                               pow(dist, BETA);
                    }
                }

                double random = distribution(rng);
                double prob = 0.0;
                int nextNode = 0;

                for (int j = 0; j < nodes.size(); ++j) {
                    if (!nodes[j]->isVisited()) {
                        double dist = nodes[currentNode]->getEdge(j)
                                      ? nodes[currentNode]->getEdge(j)->getDist()
                                      : nodes[currentNode]->getCoord().distanceTo(nodes[j]->getCoord());
                        prob += pow(pheromoneTrails[currentNode][j], ALPHA) *
                                pow(dist, BETA) / sum;
                        if (random <= prob) {
                            nextNode = j;
                            break;
                        }
                    }
                }
                antPath.path.push_back(nextNode);
                nodes[nextNode]->setVisited(true);
                currentNode = nextNode;
            }

            if (antPath.distance < bestAntPath.distance)
                bestAntPath = antPath;
            ants.push_back(antPath);
        }

        // Compare and update pheromone trails

//        vector<AntPath> ants;  // Vector of ants
        // Initialize ants (ant1 and ant2 and so on...) with the constructed paths each ant

        // Update pheromone trails based on the created ant paths
        updatePheromoneTrails(pheromoneTrails, ants, evaporationRate, pheromoneDeposit);
    }
}







