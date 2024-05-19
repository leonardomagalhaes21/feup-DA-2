#ifndef PROJ2_TSPMANAGER_H
#define PROJ2_TSPMANAGER_H

#include "Data.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <climits>
#include <iomanip>
#include <chrono>
#include <unordered_set>
#include "MutablePriorityQueue.h"

class TspManager {
public:
    TspManager();

    TspManager(const Data &d);

    void TSPbacktracking();

    void TSPprim(bool incompleteGraph);

    void printNetworkInfo(const std::string &system);

    void TSPtriangularHeuristicInput();

    void compareAlgorithmsPerformance(bool incompleteGraph);

    void dfsRealWorld();

    std::vector<Vertex<int>*> aproximationTour;
    double aproximationTourCost;

    void TSPtriangularHeuristicAlternativeInput();

private:
    Graph<int> graph;
    std::unordered_map<int, std::pair<float, float>> nodesloc;
    std::unordered_map<int, std::string> labels;

    void TSPbacktrackingMethod(std::vector<int> &bestTour, double &minTourCost);

    void TSPRec(std::vector<int> &vector1, std::vector<bool> &vector2, double d, double &cost, std::vector<int> &vector3);

    bool hasEdge(Vertex<int> *pVertex, Vertex<int> *pVertex1);

    double getEdgeWeight(Graph<int>& graph, int node, int i);

    void CompleteGraph(Graph<int> graphcopy);

    float getLatitude(Vertex<int> *vertex) const;

    float getLongitude(Vertex<int> *vertex) const;

    double haversineDistance(double lat1, double lon1, double lat2, double lon2);

    void TSPtriangularHeuristicMethod(std::vector<int> &bestTour, int startNode);




    void dfsMST(Vertex<int> *v, const std::vector<Vertex<int> *> &mst);


    void dfsMST1(Vertex<int> *v, const std::vector<Vertex<int> *> &mst);


    void
    dfsTSP(int vertex, std::unordered_set<int> &visited, std::vector<int> &tour, std::vector<int> &bestTour, double &minCost,
           double currentCost);

    Graph<int> copyGraph(const Graph<int> &originalGraph);

    void
    TSPprimMethod(const Graph<int> &graphTemp, Vertex<int> *startVertex, std::vector<Edge<int> *> &shortestPathEdges);

    void triangularHeuristicAproximation22(const int startNodeId);

    double calculateTourCost(std::vector<Vertex<int> *> tour);

};


#endif //PROJ2_TSPMANAGER_H
