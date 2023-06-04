#ifndef PROJETO_DA_MENU_H
#define PROJETO_DA_MENU_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>
#include "Graph.h"
#include "csv.h"

class Menu {
    std::string input;
    std::unordered_map<std::string,Graph*> graphs;
    std::vector<std::string> cachedGraphs;
    std::vector<std::string> headers;
    std::string func;
    std::string arg;
public:
    /**
     * @brief Constructor for the Menu class
     * @param paths the paths to the graphs that we might want to use
     */
    explicit Menu(const std::vector<std::string> &paths);
    /**
     * @brief Funtion for reading a graph and loading it to cache
     * @param path the path to the graph's csv
     */
    void readGraph(const std::string &path);
    /**
     * @brief Function for updating the cache. As some graphs have a high quantity of nodes we limit the cache to 3 graphs at each time.
     * Whenever the cache is full, the deleted graph will be the one that was used the longest time ago.
     * @param path the path to the graph's csv
     */
    void updateCache(const std::string& path);
    /**
     * @brief Function for displaying initial the menu
     * This is the menu where the user can choose which algorithm to perform.
     */
    void init();
    /**
     * @brief This function allows the user to choose which graph to use for the previously chosen algorithm
     * @paragraph headerIdx allows the function to identify which function is going to be used in order to display the correct header.
     */
    bool selectGraph(int headerIdx);
    /**
     * @brief This function shows some information about the performed algorithm such as: elapsed time, distance, etc.
     * @paragraph headerIdx allows the function to identify which function was used in order to display the correct header.
     * @param path the path to the graph's csv
     * @return true if the user wants to go to the previous menu, false if the user wants to go to the main menu
     */
    bool displayInfo(int headerIdx, const std::string &path);
    /**
     * @brief This function allows the user to choose the parameters for the ACO algorithm
     * @paragraph initialPheromones the initial pheromones amount for each edge
     * @paragraph evaporationRate the fraction of pheromones that evaporate in each iteration
     * @paragraph pheromoneDeposit the amount of pheromones that each ant deposits in each iteration
     * @paragraph numIterations the number of iterations for the ACO algorithm
     * @paragraph numAnts the number of ants for the ACO algorithm
     * @paragraph ALPHA this value determines the weight of the pheromones in the ACO algorithm
     * @paragraph BETA this value determines the weight of the distance in the ACO algorithm
     * @return true if the user wants to go to the previous menu, false if the user wants to go to the main menu
     */
    void chooseACOParams(double &initialPheromones, double &evaporationRate, double &pheromoneDeposit,
                         int &numIterations, int &numAnts, int &ALPHA, int &BETA);
    /**
     * @brief This function allows the user to display the path of the performed algorithm
     * @param path the resulting path information
     * @param graphPath the path to the graph's csv
     * @param headerIdx allows the function to identify which function was used in order to display the correct header.
     * @return true if the user wants to go to the previous menu, false if the user wants to go to the main menu
     */
    bool displayPath(const Path &path, const std::string &graphPath, int headerIdx);
    /**
     * @brief This function is used to center a string in the terminal
     * @param str the string to be centered
     * @param width the width of the terminal
     * @return the centered string
     */
    std::string static center(const std::string &str, int width);
    /**
     * @brief This function is used to "clean" the terminal by printing multiple "\n" characters
     */
    void static cleanTerminal();
};


#endif //PROJETO_DA_MENU_H
