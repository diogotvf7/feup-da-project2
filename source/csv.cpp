#include "../headers/csv.h"

#include <string>

namespace csv {

    void readNodes(const std::string &path, Graph *graph) {
        std::ifstream csv("../dataset/" + path);
        std::string buffer;
        getline(csv, buffer, '\n'); //ignore header

        while(getline(csv, buffer, '\n')) {
            Node *node;
            std::string _id, _lat, _lon;
            std::stringstream tmp(buffer);

            getline(tmp, _id, ',');
            getline(tmp, _lat, ',');
            getline(tmp, _lon, '\n');

            node = new Node(stoi(_id), Coordinate(stod(_lat), stod(_lon)));
            graph->addNode(node);
        }
    }

    void readEdges(const std::string &path, Graph *graph, bool hasHeader, bool hasLabel) {

        std::string a = "dataset/" + path;
        std::ifstream csv("dataset/" + path);
        std::string buffer;
        if (hasHeader) getline(csv, buffer, '\n'); //ignore header

        while(getline(csv, buffer, '\n')) {
            Node *src, *dest;
            std::string _src, _dest, _dist, _srcLbl, _destLbl;
            std::stringstream tmp(buffer);

            getline(tmp, _src, ',');
            getline(tmp, _dest, ',');

            if (hasLabel) {
                getline(tmp, _dist, ',');
                getline(tmp, _srcLbl, ',');
                getline(tmp, _destLbl, '\n');

                src = new Node(stoi(_src), _srcLbl);
                dest = new Node(stoi(_dest), _destLbl);
            } else {
                getline(tmp, _dist, '\n');
                src = new Node(stoi(_src));
                dest = new Node(stoi(_dest));
            }

            graph->addNode(src);
            graph->addNode(dest);
            graph->createEdge(stoi(_src), stoi(_dest), stod(_dist));
        }
    }
}