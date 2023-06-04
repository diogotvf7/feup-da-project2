#include <iomanip>
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

Path Graph::tspBacktracking() {
    vector<int> path;
    Path bestPath = {{}, INF};

    for (const auto &[key, node]: nodes)
        node->setVisited(false);

    //Node with id 0 is always our beginning and end
    Node *start = findNode(0);
    start->setVisited(true);
    path.push_back(start->getId());
    backtrack(start, path, 0, bestPath);
    bestPath.nodes.push_back(0);

    return bestPath;
}

void Graph::backtrack(Node *currentNode, std::vector<int> &path, double currentDist, Path &bestPath) {
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
        if ((currentDist + dist) < bestPath.distance) {
            bestPath.nodes = path;
            bestPath.distance = currentDist + dist;
        }
    }

    for (Edge *edge : currentNode->getAdj()) {
        Node *adjNode = edge->getDest();
        if (adjNode->isVisited()) continue;
        adjNode->setVisited(true);
        path.push_back(adjNode->getId());
        backtrack(adjNode, path, currentDist + edge->getDist(), bestPath);
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

void Graph::preOrderWalk(Node *node, std::vector<int> &path) {
    node->setVisited(true);
    for (Edge *edge : node->getAdj()) {
        Node *dest = edge->getDest();
        if (dest->getPath() == nullptr) continue;
        if (dest->getPath()->getSrc() == node) {
            path.push_back(dest->getId());
            preOrderWalk(dest, path);
        }
    }
}

Path Graph::approxTSPTour() {
    Path bestPath = {{}, 0};

    prim();
    for (const auto &[key, node] : nodes)
        node->setVisited(false);

    bestPath.nodes.push_back(0);
    preOrderWalk(findNode(0), bestPath.nodes);
    bestPath.nodes.push_back(0);
    vector<vector<double>> v;
    for (int i = 0; i < (bestPath.nodes.size() - 1); i++){
        if(findNode(bestPath.nodes[i])->getEdge(bestPath.nodes[i + 1]) == nullptr) bestPath.distance += findNode(bestPath.nodes[i])->getCoord().distanceTo(
                    findNode(bestPath.nodes[i + 1])->getCoord());
        else bestPath.distance += findNode(bestPath.nodes[i])->getEdge(bestPath.nodes[i + 1])->getDist();
    }

    return bestPath;
}

void Graph::updatePheromoneTrails(vector<vector<double>> &pheromoneTrails, const vector<Path> &ants,
                                         double evaporationRate, double pheromoneDeposit) {
    for (auto &trailRow : pheromoneTrails)
        for (auto &trail : trailRow)
            trail *= (1.0 - evaporationRate);

    for (const auto &ant : ants) {
        double pheromoneAddition = pheromoneDeposit / ant.distance;
        for (size_t i = 0; i < ant.nodes.size() - 1; ++i) {
            int src = ant.nodes[i];
            int dest = ant.nodes[i + 1];
            pheromoneTrails[src][dest] += pheromoneAddition;
            pheromoneTrails[dest][src] += pheromoneAddition;
        }
    }
}

Path Graph::aco(std::vector<std::vector<double>> &pheromoneTrails, double evaporationRate, double pheromoneDeposit,
                int numIterations, int numAnts, int ALPHA, int BETA, std::vector<std::vector<double>> &distanceCache) {
    random_device rd;
    default_random_engine rng(rd());
    uniform_real_distribution<double> distribution(0.0, 1.0);

    Path bestAntPath = {{0}, DBL_MAX};

    for (int iteration = 0; iteration < numIterations; ++iteration) {
        vector<Path> ants;
        for (int ant = 0; ant < numAnts; ++ant) {
            Path antPath = {{0}, 0};

            for (auto &[key, node] : nodes)
                node->setVisited(false);

            int currentNode = 0;
            nodes[currentNode]->setVisited(true);

            for (int i = 0; i < nodes.size() - 1; ++i) {
                double sum = 0.0;
                for (int j = 0; j < nodes.size(); ++j) {
                    if (!nodes[j]->isVisited()) {
                        sum += pow(pheromoneTrails[currentNode][j], ALPHA) *
                               pow(1 / distanceBetween(currentNode, j, distanceCache), BETA);
                    }
                }
                double random = distribution(rng);;
                double prob = 0.0;
                int nextNode = 0;
                for (int j = 0; j < nodes.size(); ++j) {
                    if (!nodes[j]->isVisited()) {
                        prob += pow(pheromoneTrails[currentNode][j], ALPHA) *
                                pow(1 / distanceBetween(currentNode, j, distanceCache), BETA) / sum;
                        if (random <= prob) {
                            nextNode = j;
                            antPath.nodes.push_back(nextNode);
                            break;
                        }
                    }
                }

                antPath.distance += distanceBetween(currentNode, nextNode, distanceCache);
                nodes[nextNode]->setVisited(true);
                currentNode = nextNode;
            }

            antPath.nodes.push_back(0);
            antPath.distance += distanceBetween(currentNode, 0, distanceCache);
            if (antPath.distance < bestAntPath.distance)
                bestAntPath = antPath;
            ants.push_back(antPath);
        }

        updatePheromoneTrails(pheromoneTrails, ants, evaporationRate, pheromoneDeposit);
    }
    return bestAntPath;
}

double Graph::distanceBetween(int src, int dest, vector<vector<double>> &distanceCache) {
    int smaller = min(src, dest);
    int larger = max(src, dest);

    if (distanceCache[smaller][larger] != -1)
        return distanceCache[smaller][larger];

    double dist = nodes[src]->getEdge(dest)
                  ? nodes[src]->getEdge(dest)->getDist()
                  : nodes[src]->getCoord().distanceTo(nodes[dest]->getCoord());
    distanceCache[smaller][larger] = dist;
    return dist;
}

double Graph::apply2OptSwap(Path &antPath, std::vector<std::vector<double>> &distanceCache, int maxIterations) {
    bool improved = true;
    double initialDistance = antPath.distance;
    while (improved && maxIterations--) {
        improved = false;
        double bestImprovement = 0.0;
        int bestI = -1;
        int bestJ = -1;

        for (size_t i = 1; i < antPath.nodes.size() - 2; ++i) {
            for (size_t j = i + 1; j < antPath.nodes.size() - 1; ++j) {
                double improvement = distanceBetween(antPath.nodes[i - 1], antPath.nodes[j], distanceCache)
                                     + distanceBetween(antPath.nodes[i], antPath.nodes[j + 1], distanceCache)
                                     - distanceBetween(antPath.nodes[i - 1], antPath.nodes[i], distanceCache)
                                     - distanceBetween(antPath.nodes[j], antPath.nodes[j + 1], distanceCache);
                if (improvement < bestImprovement) {
                    bestImprovement = improvement;
                    bestI = (int) i;
                    bestJ = (int) j;
                }
            }
        }

        if (bestI != -1 && bestJ != -1) {
            reverse(antPath.nodes.begin() + bestI, antPath.nodes.begin() + bestJ + 1);
            antPath.distance += bestImprovement;
            improved = true;
        }
    }
    return (initialDistance - antPath.distance) / initialDistance;
}


