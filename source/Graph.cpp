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

vector<int> Graph::tspBacktracking(double &bestCost) {
    vector<int> path;
    vector<int> bestPath;
    bestCost = INF;

    for (const auto &[key, node]: nodes)
        node->setVisited(false);

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
    cost = 0;
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

AntPath Graph::performACO(vector<vector<double>> &pheromoneTrails, double evaporationRate, double pheromoneDeposit,
                              int numIterations, int numAnts, int ALPHA, int BETA, vector<vector<double>> &distanceCache) {
    random_device rd;
    default_random_engine rng(rd());
    uniform_real_distribution<double> distribution(0.0, 1.0);

     ofstream file("/home/diogotvf7/Documents/2a2s/da/DA-Project2/aco-log.txt");

    AntPath bestAntPath = {{0}, DBL_MAX};

    for (int iteration = 0; iteration < numIterations; ++iteration) {
        file << "--------------------------" << endl;
        file << "|" << setw(13) << right <<  "Iteration " << setw(4) << left << iteration << setw(9) << right << "|" << endl;
        file << "--------------------------" << endl;
        vector<AntPath> ants;
        for (int ant = 0; ant < numAnts; ++ant) {
            file << "|   Ant " << ant << endl;
            int startNode = getRandomStartNode();
            AntPath antPath = {{startNode}, 0};

            for (auto &[key, node] : nodes)
                node->setVisited(false);

            int currentNode = startNode;
            nodes[currentNode]->setVisited(true);

            for (int i = 0; i < nodes.size() - 1; ++i) {
                double sum = 0.0;
                file << "|       Current node is: " << currentNode << endl;
                for (int j = 0; j < nodes.size(); ++j) {
                    if (!nodes[j]->isVisited()) {
                        sum += pow(pheromoneTrails[currentNode][j], ALPHA) *
                               pow(1 / distanceBetween(currentNode, j, distanceCache), BETA);
                        file << "|             Node " << j << " is available, dist is: " << distanceBetween(currentNode, j, distanceCache) << endl;
                    }
                }
                double random = distribution(rng);;
                double prob = 0.0;
                int nextNode = 0;
                file << "|       Random number is: " << random << endl;
                for (int j = 0; j < nodes.size(); ++j) {
                    if (!nodes[j]->isVisited()) {
                        prob += pow(pheromoneTrails[currentNode][j], ALPHA) *
                                pow(1 / distanceBetween(currentNode, j, distanceCache), BETA) / sum;
                        file << "|             Prob for node " << j << " is: " << prob << endl;
                        if (random <= prob) {
                            nextNode = j;
                            antPath.path.push_back(nextNode);
                            file << "|                  Picked node:    " << nextNode << endl;
                            file << "|                  Added distance: " << distanceBetween(currentNode, nextNode, distanceCache) << endl;
                            file << "|                  Path:";
                            for (const int &node : antPath.path)
                                file << " " << node;
                            file << endl << endl;
                            break;
                        }
                    }
                }

                antPath.distance += distanceBetween(currentNode, nextNode, distanceCache);
                nodes[nextNode]->setVisited(true);
                currentNode = nextNode;
            }

            file <<  "   Ant: " << setw(3) << right << ant << "   Distance: " << antPath.distance
                 << endl;
            if (antPath.distance == 0) {

            }

            antPath.path.push_back(startNode);
            antPath.distance += distanceBetween(currentNode, startNode, distanceCache);
            if (antPath.distance < bestAntPath.distance)
                bestAntPath = antPath;
            ants.push_back(antPath);
        }

        updatePheromoneTrails(pheromoneTrails, ants, evaporationRate, pheromoneDeposit);
    }

     file.close();

    return bestAntPath;
}

int Graph::getRandomStartNode() const {
    random_device rd;
    default_random_engine rng(rd());
    uniform_int_distribution<int> distribution(0, (int) nodes.size() - 1);
    return distribution(rng);
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

    cout << "Distance between " << src << " and " << dest << " is " << dist << endl;

    return dist;
}

void Graph::apply2OptSwap(AntPath& antPath, vector<vector<double>> &distanceCache) {
    bool improved = true;

    while (improved) {
        improved = false;
        double bestImprovement = 0.0;
        int bestI = -1;
        int bestJ = -1;

        for (size_t i = 1; i < antPath.path.size() - 2; ++i) {
            for (size_t j = i + 1; j < antPath.path.size() - 1; ++j) {
                double improvement = distanceBetween(antPath.path[i - 1], antPath.path[j], distanceCache)
                                     + distanceBetween(antPath.path[i], antPath.path[j + 1], distanceCache)
                                     - distanceBetween(antPath.path[i - 1], antPath.path[i], distanceCache)
                                     - distanceBetween(antPath.path[j], antPath.path[j + 1], distanceCache);
                if (improvement < bestImprovement) {
                    bestImprovement = improvement;
                    bestI = (int) i;
                    bestJ = (int) j;
                }
            }
        }

        if (bestI != -1 && bestJ != -1) {
            reverse(antPath.path.begin() + bestI, antPath.path.begin() + bestJ + 1);
            antPath.distance += bestImprovement;
            improved = true;
        }
    }
}


