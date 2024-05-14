#include "TspManager.h"
#include <iostream>
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
    if(!graph.getVertexSet().empty()){
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

void TspManager::TSPbacktrackingMethod(vector<int>& bestTour) {
    double minTourCost = INT_MAX;
    int startNode = 0;
    vector<int> tour = {startNode};
    vector<bool> visited(graph.getNumVertex(), false);
    visited[startNode] = true;
    TSPRec(tour,visited,0.0, minTourCost,bestTour);

}

void TspManager::TSPRec(vector<int>& tour, vector<bool>& visited, double currentCost, double& minCost, vector<int>& bestTour) {
    if (tour.size() == graph.getNumVertex()) {
        minCost = min(minCost,currentCost);
        if (currentCost == minCost) {
            bestTour = tour;
            return;
        }
    } else {
        for (int i = 0; i < graph.getNumVertex(); ++i) {
            if (!visited[i]){
               int lastNode = tour.back();//tour[tour.size()-1];
               if(hasEdge(graph.findVertex(std::to_string(lastNode)),graph.findVertex(std::to_string(i)))){
                   visited[i] = true;
                   tour.push_back(i);
                   TSPRec(tour,visited,currentCost + getEdgeWeight(graph,lastNode,i),minCost,bestTour);
                   visited[i] = false;
                   tour.pop_back();
               }
            }
        }
    }

}

bool TspManager::hasEdge(Vertex<string> *pVertex, Vertex<string> *pVertex1) {
    for (auto edge : pVertex->getAdj()) {
        if (edge->getDest() == pVertex1) {
            return true;
        }
    }

    return false;
}

double TspManager::getEdgeWeight(Graph<std::string> graph, int node, int i) {
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

void TspManager::TSPtriangularHeuristicMethod(vector<int>& bestTour) {
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


void TspManager::printNetworkInfo(const string& system){
    if (system == "real1" || system == "real2" || system == "real3") {
        for (auto node : nodesloc) {
            cout << "Vertex: " << node.first << " X: " << node.second.first << " Y: " << node.second.second << endl;
        }
    }
    else if (system == "tourism"){
        for (const auto& label : labels) {
            cout << "Vertex: " << label.first << " Label: " << label.second << endl;
        }
    }
    else if (system == "stadiums" || system == "shipping") {
        for (auto vertex : graph.getVertexSet()) {
            cout << "Vertex: " << vertex->getInfo() << endl;
        }
    }
    else {
        for (auto vertex : graph.getVertexSet()) {
            auto node = nodesloc.find(stoi(vertex->getInfo()));
            if (node != nodesloc.end()) {
                cout << "Vertex: " << vertex->getInfo() << " X: " << node->second.first << " Y: " << node->second.second << endl;
            }
        }
    }
}


//void TspManager::TSPRec(int currentIndex, int currentDist, int *currentTour, int *Tour, bool *visited, double minTourCost) {
////    if (currentIndex == graph.getNumVertex()) {
////            currentDist += graph.getEdgeWeight(currentTour[currentIndex - 1], currentTour[0]);
////            double currentCost = minTourCost;
////            for (int j = 0; j < graph.getNumVertex(); j++) {
////                currentCost += graph.getEdgeWeight(currentTour[j], currentTour[j + 1]);
////            }
////            if (currentCost < minTourCost) {
////                minTourCost = currentCost;
////                for (int j = 0; j < graph.getNumVertex(); j++) {
////                    Tour[j] = currentTour[j];
////                }
////            }
////        }
////    } else {
////        for (int j = 0; j < graph.getNumVertex(); j++) {
////            if (!visited[j] && graph.isEdge(currentTour[i1], j)) {
////                visited[j] = true;
////                currentTour[i] = j;
////                TSPRec(i + 1, j, currentTour, Tour, visited, minTourCost);
////                visited[j] = false;
////            }
////        }
////    }
////
////}
//}
//
