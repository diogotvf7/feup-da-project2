//
// Created by Jaime on 27/05/2023.
//

#include "../headers/Utils.h"
using namespace std;
#include <string>

namespace utils{

    void readToyGraphs(const std::string &path, Graph *graph){
        string folderPath = "dataset/Toy-Graphs/";

        ifstream csv(folderPath + path);
        string buffer;
        Node* nodeOrigin;
        Node* nodeDestiny;
        getline(csv, buffer, '\n'); //ignore header

        while(getline(csv, buffer, '\n')){
            string nodeIdOrigin, nodeIdDestiny, edgeValue, labelOrigem, labelDestiny;
            stringstream tmp(buffer);

            getline(tmp, nodeIdOrigin, ',');
            getline(tmp, nodeIdDestiny, ',');

            if(path == "tourism.csv"){
                getline(tmp, edgeValue, ',');
                getline(tmp, labelOrigem, ',');
                getline(tmp, labelDestiny, '\n');

                nodeOrigin = new Node(stoi(nodeIdOrigin), labelOrigem);
                nodeDestiny = new Node(stoi(nodeIdDestiny), labelDestiny);
            }else{
                getline(tmp, edgeValue, '\n');
                nodeOrigin = new Node(stoi(nodeIdOrigin));
                nodeDestiny = new Node(stoi(nodeIdDestiny));
            }


            graph->addNode(nodeOrigin);
            graph->addNode(nodeDestiny);
            graph->addEdge(stoi(nodeIdOrigin), stoi(nodeIdDestiny), stod(edgeValue));
        }
    }
}