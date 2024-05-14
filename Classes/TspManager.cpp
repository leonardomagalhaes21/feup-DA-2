#include "TspManager.h"
#include <iostream>
#include <unordered_set>

using namespace std;

TspManager::TspManager() {
    graph = {};
}

TspManager::TspManager(const Data &d) {
    graph = d.getGraph();
    nodesloc = d.getNodesLoc();
    labels = d.getLabels();
}

void TspManager::TSPbacktracking() {
    if (!graph.getVertexSet().empty()) {
        vector<int> bestTour;
        TSPbacktrackingMethod(bestTour);
        cout << "Best tour: ";
        for (int i = 0; i < bestTour.size(); i++) {
            cout << bestTour[i] << " ";
        }
        cout << bestTour[0];
        cout << endl;
    } else {
        cout << "Graph is empty" << endl;
    }
}

void TspManager::TSPbacktrackingMethod(vector<int> &bestTour) {
    double minTourCost = INT_MAX;
    int startNode = 0;
    vector<int> tour = {startNode};
    vector<bool> visited(graph.getNumVertex(), false);
    visited[startNode] = true;
    TSPRec(tour, visited, 0.0, minTourCost, bestTour);

}

void TspManager::TSPRec(vector<int> &tour, vector<bool> &visited, double currentCost, double &minCost,
                        vector<int> &bestTour) {
    if (tour.size() == graph.getNumVertex()) {
        minCost = min(minCost, currentCost);
        if (currentCost == minCost) {
            bestTour = tour;
            return;
        }
    } else {
        for (int i = 0; i < graph.getNumVertex(); ++i) {
            if (!visited[i]) {
                int lastNode = tour.back();//tour[tour.size()-1];
                if (hasEdge(graph.findVertex(std::to_string(lastNode)), graph.findVertex(std::to_string(i)))) {
                    visited[i] = true;
                    tour.push_back(i);
                    TSPRec(tour, visited, currentCost + getEdgeWeight(graph, lastNode, i), minCost, bestTour);
                    visited[i] = false;
                    tour.pop_back();
                }
            }
        }
    }

}

bool TspManager::hasEdge(Vertex<string> *pVertex, Vertex<string> *pVertex1) {
    for (auto edge: pVertex->getAdj()) {
        if (edge->getDest() == pVertex1) {
            return true;
        }
    }

    return false;
}

double TspManager::getEdgeWeight(Graph<std::string> graph, int node, int i) {
    for (auto edge: graph.findVertex(std::to_string(node))->getAdj()) {
        if (edge->getDest()->getInfo() == std::to_string(i)) {
            return edge->getWeight();
        }
    }
    return 0;
}

void TspManager::TSPtriangularHeuristic() {
    if (!graph.getVertexSet().empty()) {
        vector<int> bestTour;
        TSPtriangularHeuristicMethod(bestTour);
        cout << "Best tour: ";
        for (int i = 0; i < bestTour.size(); i++) {
            cout << bestTour[i] << " ";
        }
        cout << bestTour[0];
        cout << endl;
    } else {
        cout << "Graph is empty" << endl;
    }
}

void TspManager::TSPtriangularHeuristicMethod(vector<int> &bestTour) {
    vector<int> tour;
    vector<bool> visited(graph.getNumVertex(), false);
    int startNode = 0;
    tour.push_back(startNode);
    visited[startNode] = true;
    int currentNode = startNode;
    while (tour.size() < graph.getNumVertex()) {
        double minDist = numeric_limits<double>::max();
        int nextNode = -1;
        for (int i = 0; i < graph.getNumVertex(); i++) {
            if (!visited[i]) {
                auto nextNodev = graph.findVertex(to_string(i));
                auto currentNodev = graph.findVertex(to_string(currentNode));
                double dist = graph.getEdgeWeight(currentNodev->getInfo(), nextNodev->getInfo());
                if (dist < minDist) {
                    minDist = dist;
                    nextNode = i;
                }
            }
        }
        if (nextNode == -1) {
            break;
        }
        tour.push_back(nextNode);
        visited[nextNode] = true;
        currentNode = nextNode;
    }
    bestTour = tour;
}

template<class T>
struct CompareEdgeWeights {
    bool operator()(const Edge<T> *e1, const Edge<T> *e2) const {
        return e1->getWeight() > e2->getWeight();
    }
};

void TspManager::TSPprim() {
    CompleteGraph(graph);
    if (graph.getNumVertex() == 0) return;
    Vertex<std::string> *startVertex = graph.getVertexSet()[0];

    std::unordered_set<Vertex<std::string> *> visitedVertices;
    std::priority_queue<Edge<std::string> *, std::vector<Edge<std::string> *>, CompareEdgeWeights<std::string>> pq;
    visitedVertices.insert(startVertex);
    for (Edge<std::string> *edge: startVertex->getAdj()) {
        pq.push(edge);
    }
    std::vector<Edge<std::string> *> shortestPathEdges;


    while (!pq.empty() && visitedVertices.size() < graph.getNumVertex()) {
        Edge<std::string> *minEdge = pq.top();
        pq.pop();
        Vertex<std::string> *destVertex = minEdge->getDest();
        if (visitedVertices.find(destVertex) == visitedVertices.end()) {
            visitedVertices.insert(destVertex);
            shortestPathEdges.push_back(minEdge);
            for (Edge<std::string> *edge: destVertex->getAdj()) {
                pq.push(edge);
            }
        }
    }
    int totalWeight = 0;
    for (Edge<std::string> *edge: shortestPathEdges) {
        std::cout << edge->getOrig()->getInfo() << " -> " << edge->getDest()->getInfo() << " (Weight: "
                  << edge->getWeight() << ")" << std::endl;
        totalWeight += edge->getWeight();
    }


    if (!shortestPathEdges.empty()) {
        Vertex<std::string> *lastVertex = shortestPathEdges.back()->getDest();
        std::cout << lastVertex->getInfo() << " -> " << startVertex->getInfo() << " (Weight: "
                  << graph.getEdgeWeight(lastVertex->getInfo(), startVertex->getInfo()) << ")" << std::endl;
        totalWeight += graph.getEdgeWeight(lastVertex->getInfo(), startVertex->getInfo());
    }

    std::cout << "Total weight: " << totalWeight << std::endl;

}

float TspManager::getLatitude(Vertex<std::string> *vertex) const {
    auto it = nodesloc.find(std::stoi(vertex->getInfo()));
    if (it != nodesloc.end()) {
        return it->second.first;
    }
    return -1.0f;
}


float TspManager::getLongitude(Vertex<std::string> *vertex) const {

    auto it = nodesloc.find(std::stoi(vertex->getInfo()));
    if (it != nodesloc.end()) {

        return it->second.second;
    }

    return -1.0f;
}


void TspManager::printNetworkInfo(const string &system) {
    if (system == "real1" || system == "real2" || system == "real3") {
        for (auto node: nodesloc) {
            cout << "Vertex: " << node.first << " X: " << node.second.first << " Y: " << node.second.second << endl;
        }
    } else if (system == "tourism") {
        for (const auto &label: labels) {
            cout << "Vertex: " << label.first << " Label: " << label.second << endl;
        }
    } else if (system == "stadiums" || system == "shipping") {
        for (auto vertex: graph.getVertexSet()) {
            cout << "Vertex: " << vertex->getInfo() << endl;
        }
    } else {
        for (auto vertex: graph.getVertexSet()) {
            auto node = nodesloc.find(stoi(vertex->getInfo()));
            if (node != nodesloc.end()) {
                cout << "Vertex: " << vertex->getInfo() << " X: " << node->second.first << " Y: " << node->second.second
                     << endl;
            }
        }
    }
}

void TspManager::CompleteGraph(Graph<std::string> graphcopy) {
    std::vector<Vertex<std::string> *> vertices = graphcopy.getVertexSet();
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = i + 1; j < vertices.size(); ++j) {
            Vertex<std::string> *v1 = vertices[i];
            Vertex<std::string> *v2 = vertices[j];
            double distance = haversineDistance(getLatitude(v1), getLongitude(v1), getLatitude(v2), getLongitude(v2));
            graphcopy.addEdge(v1->getInfo(), v2->getInfo(), distance);
            graphcopy.addEdge(v2->getInfo(), v1->getInfo(), distance);
        }
    }
}

double TspManager::haversineDistance(double lat1, double lon1, double lat2, double lon2) {

    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;


    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1Rad) * cos(lat2Rad) *
               sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = 6371 * c;

    return distance;
}

