#ifndef PROJ2_TSPMANAGER_H
#define PROJ2_TSPMANAGER_H

#include "Data.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <climits>
#include <iomanip>
#include <chrono>
#include "MutablePriorityQueue.h"

class TspManager {
public :
    TspManager();

    TspManager(const Data &d);

    void TSPbacktracking();

    void TSPtriangularHeuristic();

    void TSPprim(bool incompleteGraph);

    void printNetworkInfo(const std::string &system);

    void TSPtriangularHeuristicInput();

    void compareAlgorithmsPerformance(bool incompleteGraph);


private:
    Graph<std::string> graph;
    std::unordered_map<int, std::pair<float, float>> nodesloc;
    std::unordered_map<int, std::string> labels;

    void TSPbacktrackingMethod(std::vector<int> &bestTour, double &minTourCost);

    void TSPRec(std::vector<int> &vector1, std::vector<bool> &vector2, double d, double &cost, std::vector<int> &vector3);

    bool hasEdge(Vertex<std::string> *pVertex, Vertex<std::string> *pVertex1);

    double getEdgeWeight(Graph<std::string>& graph, int node, int i);

    void TSPtriangularHeuristicMethod(std::vector<int> &vector1, double &totalWeight);

    void TSPprimMethod(const Graph<std::string>& graphTemp, Vertex<std::string> *startVertex, std::vector<Edge<std::string> *> &shortestPathEdges);

    void CompleteGraph(Graph<std::string> graphcopy);

    float getLatitude(Vertex<std::string> *vertex) const;

    float getLongitude(Vertex<std::string> *vertex) const;

    double haversineDistance(double lat1, double lon1, double lat2, double lon2);

    void TSPtriangularHeuristicMethod(std::vector<int> &bestTour, int startNode);

  
    void triangularHeuristicAproximation2(const std::string &startNodeId);


    std::vector<Vertex<std::string> *> prim(Graph<std::string> g);

    std::vector<Vertex<std::string>*> getAproximationTour() {
        return aproximationtour;
    }

    double getAproximationTourCost() {
        return aproximationtourCost;
    }

    std::vector<Vertex<std::string>*> aproximationtour;
    double aproximationtourCost;

    double calculateTourCost(std::vector<Vertex<std::string> *> vector1);

    void dfsMST(Vertex<std::string> *v, const std::vector<Vertex<std::string> *> &mst);

    Graph<std::string> copyGraph(const Graph<std::string>& originalGraph);
};


#endif //PROJ2_TSPMANAGER_H