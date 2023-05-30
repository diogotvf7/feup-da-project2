#ifndef PROJETO_DA_CSV_H
#define PROJETO_DA_CSV_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Graph.h"
#include "NodeEdge.h"

namespace csv {

    void readNodes(const std::string &path, Graph *graph);

    void readEdges(const std::string &path, Graph *graph, bool hasHeader = true, bool hasLabel = false);

}

#endif //PROJETO_DA_CSV_H
