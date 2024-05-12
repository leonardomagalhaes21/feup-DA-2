//
// Created by darksystem on 07-05-2024.
//

#ifndef PROJ2_TSPMANAGER_H
#define PROJ2_TSPMANAGER_H
#include "Data.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <climits>
#include <iomanip>

class TspManager {
public :
    TspManager();
    TspManager(const Data &d);


    void TSPbacktracking();

private:
    Graph<std::string> graph;
    std::unordered_map<int, std::pair<float, float>> nodesloc;
    std::unordered_map<int, std::string> labels;



    void TSPbacktrackingMethod(vector<int> &bestTour);

    void TSPRec(vector<int> vector1, vector<bool> vector2, double d, double cost, vector<int> &vector3);

    bool hasEdge(Vertex<string> *pVertex, Vertex<string> *pVertex1);

    double getEdgeWeight(Graph<std::string> graph, int node, int i);
};


#endif //PROJ2_TSPMANAGER_H
