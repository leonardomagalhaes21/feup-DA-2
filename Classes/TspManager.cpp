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
        std::vector<int> bestTour;
        double totalWeight = INT_MAX;
        auto start = chrono::high_resolution_clock::now();
        TSPbacktrackingMethod(bestTour, totalWeight);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        std::cout << "Best tour: ";
        for (int i : bestTour) {
            std::cout << i << " ";
        }
        cout << endl << "Total weight: " << totalWeight << endl;
        cout << "Time taken by algorithm: " << to_string(duration.count()) << " seconds" << endl;

    } else {
        std::cout << "Graph is empty" << std::endl;
    }
}

void TspManager::TSPbacktrackingMethod(std::vector<int>& bestTour, double &minTourCost) {
    int startNode = 0;
    std::vector<int> tour = { startNode };
    std::vector<bool> visited(graph.getNumVertex(), false);
    visited[startNode] = true;
    TSPRec(tour, visited, 0.0, minTourCost, bestTour);
}

void TspManager::TSPRec(std::vector<int>& tour, std::vector<bool>& visited, double currentCost, double& minCost, std::vector<int>& bestTour) {
    int numVertices = graph.getNumVertex();

    if (tour.size() == numVertices) {
        int lastNode = tour.back();
        double returnCost = getEdgeWeight(graph, lastNode, tour[0]);
        if (returnCost > 0) {
            double totalCost = currentCost + returnCost;
            if (totalCost < minCost) {
                minCost = totalCost;
                bestTour = tour;
                bestTour.push_back(tour[0]);
            }
        }
    } else {
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                int lastNode = tour.back();
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

bool TspManager::hasEdge(Vertex<std::string>* pVertex, Vertex<std::string>* pVertex1) {
    for (auto edge : pVertex->getAdj()) {
        if (edge->getDest() == pVertex1) {
            return true;
        }
    }
    return false;
}

double TspManager::getEdgeWeight(Graph<std::string>& graph, int node, int i) {
    for (auto edge : graph.findVertex(std::to_string(node))->getAdj()) {
        if (edge->getDest()->getInfo() == std::to_string(i)) {
            return edge->getWeight();
        }
    }
    return 0;
}

void TspManager::TSPtriangularHeuristic() {
    if (!graph.getVertexSet().empty()) {
        vector<int> bestTour;
        double totalWeight = 0;

        auto start = chrono::high_resolution_clock::now();

        TSPtriangularHeuristicMethod(bestTour, totalWeight);

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        totalWeight += getEdgeWeight(graph, bestTour.back(), bestTour[0]);

        cout << "Best tour: ";
        for (int i = 0; i < bestTour.size(); i++) {
            cout << bestTour[i] << " ";
        }
        cout << bestTour[0];
        cout << endl;

        cout << "Total weight: " << totalWeight << endl;
        cout << "Time taken by algorithm: " << to_string(duration.count()) << " seconds" << endl;
    } else {
        cout << "Graph is empty" << endl;
    }
}

void TspManager::TSPtriangularHeuristicMethod(vector<int> &bestTour, double &totalWeight) {
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
        totalWeight += minDist;
    }
    bestTour = tour;
}

template<class T>
struct CompareEdgeWeights {
    bool operator()(const Edge<T> *e1, const Edge<T> *e2) const {
        return e1->getWeight() > e2->getWeight();
    }
};

void TspManager::TSPprim(bool incompleteGraph) {
    if (incompleteGraph) {
        CompleteGraph(graph);
    }
    if (graph.getNumVertex() == 0) return;
    Vertex<std::string> *startVertex = graph.getVertexSet()[0];

    std::unordered_set<Vertex<std::string> *> visitedVertices;
    std::priority_queue<Edge<std::string> *, std::vector<Edge<std::string> *>, CompareEdgeWeights<std::string>> pq;
    visitedVertices.insert(startVertex);
    for (Edge<std::string> *edge: startVertex->getAdj()) {
        pq.push(edge);
    }
    std::vector<Edge<std::string> *> shortestPathEdges;

    auto start = chrono::high_resolution_clock::now();

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

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

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
    std::cout << "Time taken by algorithm: " << to_string(duration.count()) << " seconds" << std::endl;
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

void TspManager::TSPtriangularHeuristicInput() {
    if (!graph.getVertexSet().empty()) {
        int startNode;
        cout << "Enter the starting node: ";
        cin >> startNode;

        if (startNode < 0 || startNode >= graph.getNumVertex()) {
            cout << "Invalid starting node!" << endl;
            return;
        }

        vector<int> bestTour;
        TSPtriangularHeuristicMethod(bestTour, startNode);
        cout << "Best tour: ";
        int sum = 0;
        for (int i = 0; i < bestTour.size(); i++) {
            cout << bestTour[i] << " ";
            if (i > 0) {
                sum += getEdgeWeight(graph, bestTour[i-1], bestTour[i]);
            }
        }

        sum += graph.getEdgeWeight(to_string(bestTour.back()), to_string(bestTour[0]));
        cout << bestTour[0] << endl;
        cout << "Total distance: " << sum << endl;
    } else {
        cout << "Graph is empty" << endl;
    }
}

void TspManager::TSPtriangularHeuristicMethod(vector<int>& bestTour, int startNode) {
    vector<int> tour;
    vector<bool> visited(graph.getNumVertex(), false);
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

