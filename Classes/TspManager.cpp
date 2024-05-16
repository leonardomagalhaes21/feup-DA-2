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
                if (hasEdge(graph.findVertex(lastNode), graph.findVertex(i))) {
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

bool TspManager::hasEdge(Vertex<int>* pVertex, Vertex<int>* pVertex1) {
    for (auto edge : pVertex->getAdj()) {
        if (edge->getDest() == pVertex1) {
            return true;
        }
    }
    return false;
}

double TspManager::getEdgeWeight(Graph<int>& graph, int node, int i) {
    for (auto edge : graph.findVertex(node)->getAdj()) {
        if (edge->getDest()->getInfo() == i) {
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
                auto nextNodev = graph.findVertex(i);
                auto currentNodev = graph.findVertex(currentNode);
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
    Vertex<int> *startVertex = graph.getVertexSet()[0];

    std::unordered_set<Vertex<int> *> visitedVertices;
    std::priority_queue<Edge<int> *, std::vector<Edge<int> *>, CompareEdgeWeights<int>> pq;
    visitedVertices.insert(startVertex);
    for (Edge<int> *edge: startVertex->getAdj()) {
        pq.push(edge);
    }
    std::vector<Edge<int> *> shortestPathEdges;

    auto start = chrono::high_resolution_clock::now();

    while (!pq.empty() && visitedVertices.size() < graph.getNumVertex()) {
        Edge<int> *minEdge = pq.top();
        pq.pop();
        Vertex<int> *destVertex = minEdge->getDest();
        if (visitedVertices.find(destVertex) == visitedVertices.end()) {
            visitedVertices.insert(destVertex);
            shortestPathEdges.push_back(minEdge);
            for (Edge<int> *edge: destVertex->getAdj()) {
                pq.push(edge);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    int totalWeight = 0;
    for (Edge<int> *edge: shortestPathEdges) {
        std::cout << edge->getOrig()->getInfo() << " -> " << edge->getDest()->getInfo() << " (Weight: "
                  << edge->getWeight() << ")" << std::endl;
        totalWeight += edge->getWeight();
    }

    if (!shortestPathEdges.empty()) {
        Vertex<int> *lastVertex = shortestPathEdges.back()->getDest();
        std::cout << lastVertex->getInfo() << " -> " << startVertex->getInfo() << " (Weight: "
                  << graph.getEdgeWeight(lastVertex->getInfo(), startVertex->getInfo()) << ")" << std::endl;
        totalWeight += graph.getEdgeWeight(lastVertex->getInfo(), startVertex->getInfo());
    }

    std::cout << "Total weight: " << totalWeight << std::endl;
    std::cout << "Time taken by algorithm: " << to_string(duration.count()) << " seconds" << std::endl;
}

float TspManager::getLatitude(Vertex<int> *vertex) const {
    auto it = nodesloc.find(vertex->getInfo());
    if (it != nodesloc.end()) {
        return it->second.first;
    }
    return -1.0f;
}


float TspManager::getLongitude(Vertex<int> *vertex) const {

    auto it = nodesloc.find(vertex->getInfo());
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
            auto node = nodesloc.find(vertex->getInfo());
            if (node != nodesloc.end()) {
                cout << "Vertex: " << vertex->getInfo() << " X: " << node->second.first << " Y: " << node->second.second
                     << endl;
            }
        }
    }
}

void TspManager::CompleteGraph(Graph<int> graphcopy) {
    std::vector<Vertex<int> *> vertices = graphcopy.getVertexSet();
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = i + 1; j < vertices.size(); ++j) {
            Vertex<int> *v1 = vertices[i];
            Vertex<int> *v2 = vertices[j];
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
        //triangularHeuristicAproximation2(to_string(startNode));
        cout << "Best tour: ";
        int sum = 0;
        for (int i = 0; i < bestTour.size(); i++) {
            cout << bestTour[i] << " ";
            if (i > 0) {
                sum += getEdgeWeight(graph, bestTour[i-1], bestTour[i]);
            }
        }

        sum += graph.getEdgeWeight(bestTour.back(), bestTour[0]);
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
                auto nextNodev = graph.findVertex(i);
                auto currentNodev = graph.findVertex(currentNode);
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




//TESTIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIING

/*void TspManager::TSPRealWorldInput() {
    if (!graph.getVertexSet().empty()) {
        int startNode;
        std::cout << "Enter the starting node: ";
        std::cin >> startNode;

        if (startNode < 0 || startNode >= graph.getNumVertex()) {
            std::cout << "Invalid starting node!" << std::endl;
            return;
        }
        triangularHeuristicAproximation22(startNode);

        std::cout << "Best tour: ";
        double sum = 0.0;
        for (size_t i = 0; i < aproximationtour.size(); i++) {
            std::cout << aproximationtour[i]->getInfo() << " ";
            if (i > 0) {
                sum += getEdgeWeight(graph, aproximationtour[i-1]->getInfo(), aproximationtour[i]->getInfo());
            }
        }

        sum += getEdgeWeight(graph, aproximationtour.back()->getInfo(), aproximationtour[0]->getInfo());
        std::cout << aproximationtour[0]->getInfo() << std::endl;
        std::cout << "Total distance: " << sum << std::endl;
    }
}*/



std::vector<Vertex<int> *> prim(Graph<int> * g) {
    if (g->getVertexSet().empty()) {
        return g->getVertexSet();
    }
    for(auto v : g->getVertexSet()) {
        v->setDist(INT_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex<int>* s = g->getVertexSet().front();
    s->setDist(0);
    MutablePriorityQueue<Vertex<int>> q;
    q.insert(s);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex<int>* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());

                    w->setPath(e);
                    if (oldDist == INT_MAX) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    return g->getVertexSet();
}

void TspManager::dfsMST(Vertex<int>* v, const vector<Vertex<int>*>& mst) {
    v->setVisited(true);

    if (std::find(aproximationtour.begin(), aproximationtour.end(), v) == aproximationtour.end()) {
        aproximationtour.push_back(v);
    }

    for (auto& edge : v->getAdj()) {
        Vertex<int>* neighbor = edge->getDest();
        if (!neighbor->isVisited()) {
            aproximationtourCost += edge->getWeight();
            dfsMST(neighbor, mst);
        }
    }
}



void TspManager::triangularHeuristicAproximation22(const int startNodeId) {
    aproximationtour.clear();
    aproximationtourCost = 0.0;

    Vertex<int>* startVertex = graph.findVertex(startNodeId);
    if (!startVertex) {
        cerr << "Start node not found in the graph.\n";
        return;
    }

    std::vector<Vertex<int>*> mst = prim(&graph);

    for(auto v : graph.getVertexSet()) {
        v->setVisited(false);
    }
    Graph<int> mstGraph;
    for(auto v : mst) {
        mstGraph.addVertex(v->getInfo());
        auto ep = v->getPath();
        if (ep != nullptr) {
            if(!mstGraph.addBidirectionalEdge(ep->getOrig()->getInfo(),ep->getDest()->getInfo(),ep->getWeight())) {
                mstGraph.addVertex(ep->getOrig()->getInfo());
                mstGraph.addVertex(ep->getDest()->getInfo());
                mstGraph.addBidirectionalEdge(ep->getOrig()->getInfo(),ep->getDest()->getInfo(),ep->getWeight());
            }
        }
    }
    //dfsMST(startVertex, mstGraph.getVertexSet());
    auto vector1 = mstGraph.dfs();
    for(auto s: vector1) {
        aproximationtour.push_back(graph.findVertex(s));
    }
    aproximationtour.push_back(startVertex);

    aproximationtourCost = calculateTourCost(aproximationtour);
    //resetNodesVisitation();
}

double TspManager::calculateTourCost(std::vector<Vertex<int> *> tour) {
    double totalCost = 0.0;

    // Iterate through the tour vector to accumulate the edge weights
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        Vertex<int>* current = tour[i];
        Vertex<int>* next = tour[i + 1];

        // Find the edge connecting current to next
        bool edgeFound = false;
        for (auto& edge : current->getAdj()) {
            if (edge->getDest() == next) {
                totalCost += edge->getWeight();
                edgeFound = true;
                break;
            }
        }

        // Handle the case if an edge is not found (graph might be incomplete or tour might be incorrect)
        if (!edgeFound) {
            std::cerr << "Edge not found between " << current->getInfo() << " and " << next->getInfo() << "\n";
            return -1; // or any other error handling
        }
    }

    // Since the tour should return to the start vertex, add the cost of returning to the first vertex
    Vertex<int>* last = tour.back();
    Vertex<int>* first = tour.front();

    bool returnEdgeFound = false;
    for (auto& edge : last->getAdj()) {
        if (edge->getDest() == first) {
            totalCost += edge->getWeight();
            returnEdgeFound = true;
            break;
        }
    }

    if (!returnEdgeFound) {
        std::cerr << "Return edge not found between " << last->getInfo() << " and " << first->getInfo() << "\n";
        return -1; // or any other error handling
    }

    return totalCost;
}

// Inside TspManager class

void TspManager::TSPRealWorldInput() {
    if (!graph.getVertexSet().empty()) {
        int startNode;
        std::cout << "Enter the starting node: ";
        std::cin >> startNode;

        if (startNode < 0 || startNode >= graph.getNumVertex()) {
            std::cout << "Invalid starting node!" << std::endl;
            return;
        }

        aproximationtour.clear();
        aproximationtourCost = 0.0;

        Vertex<int>* startVertex = graph.findVertex(startNode);
        if (!startVertex) {
            std::cerr << "Start node not found in the graph.\n";
            return;
        }

        std::vector<Vertex<int>*> mst = prim(&graph);
        for (auto v : graph.getVertexSet()) {
            v->setVisited(false);
        }

        dfsMST(startVertex, mst);

        if (aproximationtour.empty()) {
            std::cout << "No path exists for the specified starting node!" << std::endl;
            return;
        }

        std::cout << "Best tour: ";
        double sum = aproximationtourCost;
        for (size_t i = 0; i < aproximationtour.size(); i++) {
            std::cout << aproximationtour[i]->getInfo() << " ";
        }

        std::cout << aproximationtour[0]->getInfo() << std::endl;
        std::cout << "Total distance: " << std::fixed << std::setprecision(2) << sum << std::endl;
    } else {
        std::cout << "Graph is empty" << std::endl;
    }
}



void TspManager::dfsMST1(Vertex<int>* v, const std::vector<Vertex<int>*>& mst) {
    v->setVisited(true);
    aproximationtour.push_back(v);

    for (auto& edge : v->getAdj()) {
        Vertex<int>* neighbor = edge->getDest();
        if (!neighbor->isVisited()) {
            aproximationtourCost += edge->getWeight();
            dfsMST1(neighbor, mst);
        }
    }
}

void TspManager::dfsTSP(int vertex, unordered_set<int>& visited, vector<int>& tour, vector<int>& bestTour, double& minCost, double currentCost) {
    visited.insert(vertex);
    tour.push_back(vertex);
    if (visited.size() == graph.getNumVertex()) {
        if (hasEdge(graph.findVertex(tour.back()), graph.findVertex(tour.front()))) {
            currentCost += getEdgeWeight(graph, tour.back(), tour.front());
            if (currentCost < minCost) {
                minCost = currentCost;
                bestTour = tour;
            }
        }
    } else {
        for (auto adjEdge : graph.findVertex(vertex)->getAdj()) {
            auto neighbor = adjEdge->getDest()->getInfo();
            if (visited.find(neighbor) == visited.end()) {
                dfsTSP(neighbor, visited, tour, bestTour, minCost, currentCost + adjEdge->getWeight());
            }
        }
    }
    visited.erase(vertex);
    tour.pop_back();
}

void TspManager::runModifiedDFS(int startVertex) {
    if (graph.getVertexSet().empty()) {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
        return;
    }

    unordered_set<int> visited;
    vector<int> tour;
    vector<int> bestTour;
    double minCost = numeric_limits<double>::max();
    dfsTSP(startVertex, visited, tour, bestTour, minCost, 0);

    if (!bestTour.empty() && bestTour.front() == startVertex && hasEdge(graph.findVertex(bestTour.back()), graph.findVertex(bestTour.front()))) {
        printTourCostModified(bestTour);
    } else {
        cout << "No path exists that returns to the origin and visits all nodes.\n";
    }
}

void TspManager::TSPRealWorldInput1() {
    if (graph.getVertexSet().empty()) {
        cout << "Graph data is empty. Please parse the CSV file first.\n";
        return;
    }

    // Choose an appropriate starting vertex
    int startVertex = 0; // You may need to change this based on your specific requirements

    // Run modified DFS to find the best tour
    runModifiedDFS(startVertex);
}

void TspManager::printTourCostModified(const vector<int>& tour) {
    cout << "Best tour: ";
    for (int vertex : tour) {
        cout << vertex << " ";
    }
    cout << tour.front(); // Printing the starting vertex again to complete the tour
    cout << endl;

    // Calculate the total cost of the tour
    double totalCost = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        totalCost += getEdgeWeight(graph, tour[i], tour[i + 1]);
    }
    // Add the cost of returning to the starting vertex
    totalCost += getEdgeWeight(graph, tour.back(), tour.front());

    cout << "Total cost: " << totalCost << endl;
}

void TspManager::compareAlgorithmsPerformance(bool incompleteGraph) {
    std::vector<int> bestTour;
    double totalWeight = INT_MAX;

    auto start = chrono::high_resolution_clock::now();
    TSPbacktrackingMethod(bestTour, totalWeight);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    std::cout << "Total weight: " << totalWeight << std::endl;
    std::cout << "Time taken by backtracking algorithm: " << to_string(duration.count()) << " seconds" << std::endl;
    cout << "----------------//----------------" << endl;

    bestTour = {};
    totalWeight = 0;
    start = chrono::high_resolution_clock::now();
    TSPtriangularHeuristicMethod(bestTour, totalWeight);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    totalWeight += getEdgeWeight(graph, bestTour.back(), bestTour[0]);
    std::cout << "Total weight: " << totalWeight << std::endl;
    std::cout << "Time taken by triangular heuristic algorithm: " << to_string(duration.count()) << " seconds" << std::endl;
    cout << "----------------//----------------" << endl;

    totalWeight = 0;
    Graph<int> graphTemp = copyGraph(graph);
    if (incompleteGraph)
        CompleteGraph(graphTemp);
    std::vector<Edge<int> *> shortestPathEdges;
    start = chrono::high_resolution_clock::now();
    TSPprimMethod(graphTemp, graphTemp.getVertexSet()[0], shortestPathEdges);
    end = chrono::high_resolution_clock::now();
    for (Edge<int> *edge: shortestPathEdges) {
        totalWeight += edge->getWeight();
    }
    if (!shortestPathEdges.empty()) {
        Vertex<int> *lastVertex = shortestPathEdges.back()->getDest();
        totalWeight += graphTemp.getEdgeWeight(lastVertex->getInfo(), graphTemp.getVertexSet()[0]->getInfo());
    }
    duration = end - start;
    std::cout << "Total weight: " << totalWeight << std::endl;
    std::cout << "Time taken by prim algorithm: " << to_string(duration.count()) << " seconds" << std::endl;
}

Graph<int> TspManager::copyGraph(const Graph<int>& originalGraph) {
    Graph<int> copiedGraph;

    for (auto v : originalGraph.getVertexSet()) {
        copiedGraph.addVertex(v->getInfo());
    }

    for (auto v : originalGraph.getVertexSet()) {
        for (auto e : v->getAdj()) {
            copiedGraph.addEdge(v->getInfo(), e->getDest()->getInfo(), e->getWeight());
        }
    }

    return copiedGraph;
}

void TspManager::TSPprimMethod(const Graph<int>& graphTemp, Vertex<int> *startVertex, std::vector<Edge<int> *> &shortestPathEdges) {
    if (graphTemp.getNumVertex() == 0) return;

    std::unordered_set<Vertex<int> *> visitedVertices;
    std::priority_queue<Edge<int> *, std::vector<Edge<int> *>, CompareEdgeWeights<int>> pq;
    visitedVertices.insert(startVertex);
    for (Edge<int> *edge: startVertex->getAdj()) {
        pq.push(edge);
    }

    while (!pq.empty() && visitedVertices.size() < graphTemp.getNumVertex()) {
        Edge<int> *minEdge = pq.top();
        pq.pop();
        Vertex<int> *destVertex = minEdge->getDest();
        if (visitedVertices.find(destVertex) == visitedVertices.end()) {
            visitedVertices.insert(destVertex);
            shortestPathEdges.push_back(minEdge);
            for (Edge<int> *edge: destVertex->getAdj()) {
                pq.push(edge);
            }
        }
    }
}


