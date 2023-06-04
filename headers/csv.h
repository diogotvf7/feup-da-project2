#ifndef PROJETO_DA_CSV_H
#define PROJETO_DA_CSV_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "NodeEdge.h"

namespace csv {
    /**
     * @brief Reads the nodes from a csv file and adds them to the graph
     * @param path the path to the csv file
     * @param graph the graph to which we want to add the nodes
     */
    void readNodes(const std::string &path, Graph *graph);
    /**
     * @brief Reads the edges from a csv file and adds them to the graph
     * @param path the path to the csv file
     * @param graph the graph to which we want to add the edges
     * @param hasHeader true if the csv file has an header, false otherwise
     * @param hasLabel true if the csv file has a label, false otherwise
     */
    void readEdges(const std::string &path, Graph *graph, bool hasHeader = true, bool hasLabel = false);
}

#endif //PROJETO_DA_CSV_H
