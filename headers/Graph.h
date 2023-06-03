#ifndef GRAPH_H
#define GRAPH_H

#include <random>
#include <chrono>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cfloat>
#include "NodeEdge.h"
#include "MutablePriorityQueue.h"


#include <fstream>


#define INF INT32_MAX
#define node_map std::unordered_map<int, Node*>

/**
 * @brief Struct for saving a path's information
 * @param nodes the nodes of the path
 * @param distance the distance of the path
 */
struct Path {
    std::vector<int> nodes;
    double distance;
};

class Graph {
    node_map nodes;

public:
    /**
     * @brief Function for finding a node in the graph
     * @param idNode the id of the node we want to find
     * Complexity: O(1) as it uses an unordered_map and all keys are unique
     * @return the node with the given id
     */
    Node *findNode(const int &idNode) const;
    /**
     * @brief Function for adding a node to the graph
     * @param node the node we want to add to the graph
     */
    void addNode(Node *node);
    /**
     * @brief Get function for the graph's nodes
     * @return returns the graph's nodes
     */
    node_map getNodes() const;
    /**
     * @brief Function for adding a bidirectional edge to the graph
     * @param src the id of the source node
     * @param dest the id of the destination node
     * @param dist the distance between the two nodes
     */
    void createEdge(const int &src, const int &dest, double dist) const;
    /**
     * @brief Function that checks the distance between two nodes. In order to avoid recalculating the same distance multiple times, it uses a cache to store the distances between nodes. If the distance between the two nodes is not in the cache, it calculates it and stores it in the cache.
     * @param src the id of the source node
     * @param dest the id of the destination node
     * @param cache the cache that stores the distances between nodes
     * @return returns the distance between the two nodes
     */
    double distanceBetween(int src, int dest, std::vector<std::vector<double>> &cache);

    /*First Exercise*/
    /**
     * @brief Caller function for the backtracking approach for solving the TSP in a graph
     * @return returns the path with the minimum distance
     */
    Path tspBacktracking();
    /**
     * @brief Function that performs the backtracking approach for solving the TSP in a graph
     * Complexity: O(n!) where n is the number of nodes. This high complexity is due to the fact that this algorithm has to calculate every possible permutation of the nodes in the graph.
     * @param currentNode the current node
     * @param path the path that is being built
     * @param currentDist the current distance of the path
     * @param bestPath the the minimum distance path's information
     */
    void backtrack(Node *currentNode, std::vector<int> &path, double currentDist, Path &bestPath);

    /*Second Exercise*/
    /**
     * @brief Function that performs the Prim's algorithm for finding the minimum spanning tree of a graph
     * Complexity: O((V + E) log V) where E is the number of edges and V is the number of vertices.
     * @return returns the minimum spanning tree
     */
    void prim();
    /**
     * @brief Function that performs the pre-order walk of a tree
     * Complexity: O(V + E) where V is the number of vertices and E is the number of edges. This complexity is due to the fact that this algorithm has to visit every node and, in the worst case, every edge in the tree.
     * @param node the current node
     * @param path the path that is being built
     */
    void preOrderWalk(Node *node, std::vector<int> &path);
    /**
     * @brief Function that performs the triangular approximation algorithm for solving the TSP in a graph
     * Complexity: O((V + E) log V) + O(V + E) + O(V) which is equivalent to O((V + E) log V) where V is the number of vertices and E is the number of edges. This complexity is due to the fact that this algorithm uses Prim's algorithm to find the minimum spanning tree and then it uses the pre-order walk to find the path.
     * @return returns the path with the minimum distance
     */
    Path approxTSPTour();

    /*Third Exercise*/
    /**
     * @brief Function that updates the pheromone trails of the graph
     * Complexity: O((E^2) + (A * N)) where A is the number of ants, N is the number of nodes and E is the number of edges of the graph. This complexity is due to the fact that this algorithm has to update the pheromone trails for every ant and that for every edge of the graph the pheromones evaporation must be applied.
     * @param pheromoneTrails the pheromone trails of the graph
     * @param ants the ants that are currently in the graph
     * @param evaporationRate the evaporation rate of the pheromones
     * @param pheromoneDeposit the amount of pheromones that are deposited in the pheromone trails
     */
    static void updatePheromoneTrails(std::vector<std::vector<double>>& pheromoneTrails,
                                      const std::vector<Path> &ants,
                                      double evaporationRate, double pheromoneDeposit);

    /**
     * @brief Function that performs the ant colony optimization algorithm for solving the TSP in a graph
     * Complexity: O(I * A * (N^2 + (E^2 + A * N))) where I is the number of iterations, A is the number of ants, N is the number of nodes and E is the number of edges of the graph. This complexity is due to the fact for every iteration, each ant has to build a path (this action may, in the worst case, iterate through every node twice, hence the N²) and also has to update the pheromone trails (this action has a complexity of E² + A * N).
     * @param pheromoneTrails the pheromone trails of the graph
     * @param evaporationRate the evaporation rate of the pheromones
     * @param pheromoneDeposit the amount of pheromones that are deposited in the pheromone trails
     * @param numIterations the number of iterations of the algorithm
     * @param numAnts the number of ants that are going to be used in the algorithm
     * @param ALPHA the alpha parameter of the algorithm
     * @param BETA the beta parameter of the algorithm
     * @param distanceCache the cache that stores the distances between nodes
     * @return returns the path with the minimum distance
     */
    Path aco(std::vector<std::vector<double>> &pheromoneTrails,
             double evaporationRate, double pheromoneDeposit,
             int numIterations, int numAnts, int ALPHA, int BETA,
             std::vector<std::vector<double>> &distanceCache);

    /**
     * @brief Function that performs the 2 optimization swap algorithm for improving a path presented as a TSP solution
     * Complexity: O(I * N²) where I is the number of iterations and N is the number of nodes. This complexity is due to the fact that for every iteration, the algorithm has to iterate through every node twice (hence the N²).
     * @param antPath the path to be improved
     * @param distanceCache the cache that stores the distances between nodes
     * @param maxIterations the maximum number of iterations of the algorithm, -1 if there is no limit
     * @return returns the fraction of the improvement
     */
    double apply2OptSwap(Path &antPath, std::vector<std::vector<double>> &distanceCache, int maxIterations = INT32_MAX);
};

/*                           Performance analysis                           */

/**
 * @brief Template function that measures the execution time of a function
 * @tparam Func The function type
 * @tparam Object The object type
 * @tparam Args Packet template for the arguments types
 * @param elapsedTime reference to the variable that will store the elapsed time
 * @param object object that will be used to call the function
 * @param func function that will be called
 * @param args arguments of the function
 * @return returns the result of the function
 */
template<typename Func, typename Object, typename... Args>
auto measureExecutionTime(double &elapsedTime, Object&& object, Func&& func, Args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();

    auto result = (std::forward<Object>(object).*std::forward<Func>(func))(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;

    elapsedTime = duration.count();

    return result;
}

#endif //GRAPH_H
