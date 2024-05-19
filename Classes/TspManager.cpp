#include "TspManager.h"

using namespace std;

TspManager::TspManager() {
    graph = {};
}

TspManager::TspManager(const Data &d) {
    graph = d.getGraph();
    nodesloc = d.getNodesLoc();
    labels = d.getLabels();
}

void TspManager::tspBacktracking() {
    if (!graph.getVertexSet().empty()) {
        vector<int> bestTour;
        double totalWeight = INT_MAX;
        auto start = chrono::high_resolution_clock::now();
        tspBacktrackingMethod(bestTour, totalWeight);
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double> duration = end - start;

        cout << "Best tour: ";
        for (int i: bestTour) {
            cout << i << " ";
        }
        cout << endl << "Total weight: " << totalWeight << endl;
        cout << "Time taken by algorithm: " << to_string(duration.count()) << " seconds" << endl;

    } else {
        cout << "Graph is empty" << endl;
    }
}

void TspManager::tspBacktrackingMethod(vector<int> &bestTour, double &minTourCost) {
    int startNode = 0;
    vector<int> tour = {startNode};
    vector<bool> visited(graph.getNumVertex(), false);
    visited[startNode] = true;
    tspRec(tour, visited, 0.0, minTourCost, bestTour);
}

void TspManager::tspRec(vector<int> &tour, vector<bool> &visited, double currentCost, double &minCost,
                        vector<int> &bestTour) {
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
                    tspRec(tour, visited, currentCost + getEdgeWeight(graph, lastNode, i), minCost, bestTour);
                    visited[i] = false;
                    tour.pop_back();
                }
            }
        }
    }
}

bool TspManager::hasEdge(Vertex<int> *pVertex, Vertex<int> *pVertex1) {
    for (auto edge: pVertex->getAdj()) {
        if (edge->getDest() == pVertex1) {
            return true;
        }
    }
    return false;
}

double TspManager::getEdgeWeight(Graph<int> &graph, int node, int i) {
    for (auto edge: graph.findVertex(node)->getAdj()) {
        if (edge->getDest()->getInfo() == i) {
            return edge->getWeight();
        }
    }
    return 0;
}

template<class T>
struct CompareEdgeWeights {
    bool operator()(const Edge<T> *e1, const Edge<T> *e2) const {
        return e1->getWeight() > e2->getWeight();
    }
};

void TspManager::tspPrim(bool incompleteGraph) {
    if (incompleteGraph) {
        completeGraph(graph);
    }
    if (graph.getNumVertex() == 0) return;
    Vertex<int> *startVertex = graph.getVertexSet()[0];

    unordered_set<Vertex<int> *> visitedVertices;
    priority_queue<Edge<int> *, vector<Edge<int> *>, CompareEdgeWeights<int>> pq;
    visitedVertices.insert(startVertex);
    for (Edge<int> *edge: startVertex->getAdj()) {
        pq.push(edge);
    }
    vector<Edge<int> *> shortestPathEdges;

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
        cout << edge->getOrig()->getInfo() << " -> " << edge->getDest()->getInfo() << " (Weight: "
             << edge->getWeight() << ")" << endl;
        totalWeight += edge->getWeight();
    }

    if (!shortestPathEdges.empty()) {
        Vertex<int> *lastVertex = shortestPathEdges.back()->getDest();
        cout << lastVertex->getInfo() << " -> " << startVertex->getInfo() << " (Weight: "
             << graph.getEdgeWeight(lastVertex->getInfo(), startVertex->getInfo()) << ")" << endl;
        totalWeight += graph.getEdgeWeight(lastVertex->getInfo(), startVertex->getInfo());
    }

    cout << "Total weight: " << totalWeight << endl;
    cout << "Time taken by algorithm: " << to_string(duration.count()) << " seconds" << endl;
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

void TspManager::completeGraph(Graph<int> graphCopy) {
    vector<Vertex<int> *> vertices = graphCopy.getVertexSet();
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = i + 1; j < vertices.size(); ++j) {
            Vertex<int> *v1 = vertices[i];
            Vertex<int> *v2 = vertices[j];
            double distance = haversineDistance(getLatitude(v1), getLongitude(v1), getLatitude(v2), getLongitude(v2));
            graphCopy.addEdge(v1->getInfo(), v2->getInfo(), distance);
            graphCopy.addEdge(v2->getInfo(), v1->getInfo(), distance);
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

void TspManager::tspTriangularHeuristicInput() {
    if (!graph.getVertexSet().empty()) {
        int startNode;
        cout << "Enter the starting node: ";
        cin >> startNode;

        if (startNode < 0 || startNode >= graph.getNumVertex()) {
            cout << "Invalid starting node!" << endl;
            return;
        }

        vector<int> bestTour;

        auto start = chrono::high_resolution_clock::now();
        tspTriangularHeuristicMethod(bestTour, startNode);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Best tour: ";
        int sum = 0;
        for (int i = 0; i < bestTour.size(); i++) {
            cout << bestTour[i] << " ";
            if (i > 0) {
                sum += getEdgeWeight(graph, bestTour[i - 1], bestTour[i]);
            }
        }

        sum += graph.getEdgeWeight(bestTour.back(), bestTour[0]);
        cout << bestTour[0] << endl;
        cout << "Total distance: " << sum << endl;
        cout << "Time taken by the algorithm: " << to_string(duration.count()) << " seconds" << endl;
    } else {
        cout << "Graph is empty" << endl;
    }
}

void TspManager::tspTriangularHeuristicMethod(vector<int> &bestTour, int startNode) {
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
                auto v = graph.findVertex(i);
                auto v2 = graph.findVertex(currentNode);
                double dist = graph.getEdgeWeight(v2->getInfo(), v->getInfo());
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


vector<Vertex<int> *> TspManager::primMPQ(Graph<int> *g) {
    if (g->getVertexSet().empty()) {
        return g->getVertexSet();
    }
    for (auto v: g->getVertexSet()) {
        v->setDist(INT_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }
    Vertex<int> *s = g->getVertexSet().front();
    s->setDist(0);
    MutablePriorityQueue<Vertex<int>> q;
    q.insert(s);
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);
        for (auto &e: v->getAdj()) {
            Vertex<int> *w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if (e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());

                    w->setPath(e);
                    if (oldDist == INT_MAX) {
                        q.insert(w);
                    } else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    return g->getVertexSet();
}

void TspManager::compareAlgorithmsPerformance() {
    vector<int> bestTour;
    double totalWeight = INT_MAX;

    auto start = chrono::high_resolution_clock::now();
    tspBacktrackingMethod(bestTour, totalWeight);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Total weight: " << totalWeight << endl;
    cout << "Time taken by backtracking algorithm: " << to_string(duration.count()) << " seconds" << endl;
    cout << "----------------//----------------" << endl;

    totalWeight = 0.0;
    bestTour = {};
    start = chrono::high_resolution_clock::now();
    tspTriangularHeuristicMethod(bestTour, 0);
    end = chrono::high_resolution_clock::now();
    duration = end - start;
    for (int i = 0; i < bestTour.size(); i++) {
        if (i > 0) {
            totalWeight += getEdgeWeight(graph, bestTour[i - 1], bestTour[i]);
        }
    }
    totalWeight += graph.getEdgeWeight(bestTour.back(), bestTour[0]);
    cout << "Total weight: " << totalWeight << endl;
    cout << "Time taken by triangular heuristic algorithm: " << to_string(duration.count()) << " seconds" << endl;
    cout << "----------------//----------------" << endl;

    totalWeight = 0;
    Graph<int> graphTemp = copyGraph(graph);
    vector<Edge<int> *> shortestPathEdges;
    start = chrono::high_resolution_clock::now();
    tspPrimMethod(graphTemp, graphTemp.getVertexSet()[0], shortestPathEdges);
    end = chrono::high_resolution_clock::now();
    for (Edge<int> *edge: shortestPathEdges) {
        totalWeight += edge->getWeight();
    }
    if (!shortestPathEdges.empty()) {
        Vertex<int> *lastVertex = shortestPathEdges.back()->getDest();
        totalWeight += graphTemp.getEdgeWeight(lastVertex->getInfo(), graphTemp.getVertexSet()[0]->getInfo());
    }
    duration = end - start;
    cout << "Total weight: " << totalWeight << endl;
    cout << "Time taken by Prim's algorithm: " << to_string(duration.count()) << " seconds" << endl;
}

Graph<int> TspManager::copyGraph(const Graph<int> &originalGraph) {
    Graph<int> copiedGraph;

    for (auto v: originalGraph.getVertexSet()) {
        copiedGraph.addVertex(v->getInfo());
    }

    for (auto v: originalGraph.getVertexSet()) {
        for (auto e: v->getAdj()) {
            copiedGraph.addEdge(v->getInfo(), e->getDest()->getInfo(), e->getWeight());
        }
    }

    return copiedGraph;
}

void TspManager::tspPrimMethod(const Graph<int> &graphTemp, Vertex<int> *startVertex, vector<Edge<int> *> &shortestPathEdges) {
    if (graphTemp.getNumVertex() == 0) return;

    unordered_set<Vertex<int> *> visitedVertices;
    priority_queue<Edge<int> *, vector<Edge<int> *>, CompareEdgeWeights<int>> pq;
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

void TspManager::kruskalRealWorld(){
    int source;
    cout << "Enter the starting node: ";
    cin >> source;

    auto start = chrono::high_resolution_clock::now();
    auto res = graph.kruskalMST(source);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    double totalWeight = 0.0;
    cout << res[0].getOrig()->getInfo() << " ";
    for (auto i : res){
        cout << i.getDest()->getInfo() << " ";
        totalWeight += i.getWeight();
    }
    for (auto e : res.back().getDest()->getAdj()){
        if (e->getDest()->getInfo() == res[0].getOrig()->getInfo()) {
            cout << e->getDest()->getInfo() << endl;
            totalWeight += e->getWeight();
            break;
        }
    }

    cout << endl;
    cout << "Total weight: " << fixed << setprecision(2) << totalWeight << endl;
    cout << "Time taken by Kruskal's algorithm: " << to_string(duration.count()) << " seconds" << endl;
}


void TspManager::tspTriangularHeuristicAlternativeInput() {
    vector<Vertex<int>*> aproximationTour;
    double aproximationTourCost;

    if (!graph.getVertexSet().empty()) {
        int startNode;
        cout << "Enter the starting node: ";
        cin >> startNode;

        if (startNode < 0 || startNode >= graph.getNumVertex()) {
            cout << "Invalid starting node!" << endl;
            return;
        }
        auto start = chrono::high_resolution_clock::now();
        triangularHeuristicAproximation(startNode, aproximationTour, aproximationTourCost);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Best tour: ";
        for (auto & i : aproximationTour) {
            cout << i->getInfo() << " ";
        }

        cout << aproximationTour[0]->getInfo() << endl;
        cout << "Total distance: " << fixed << setprecision(2) << aproximationTourCost << endl;
        cout << "Time taken by the algorithm: " << to_string(duration.count()) << " seconds" << endl;
    }
}

void TspManager::triangularHeuristicAproximation(const int startNodeId, std::vector<Vertex<int> *> &aproximationTour, double &aproximationTourCost) {
    aproximationTour.clear();
    aproximationTourCost = 0.0;

    Vertex<int> *startVertex = graph.findVertex(startNodeId);
    if (!startVertex) {
        cerr << "Start node not found in the graph.\n";
        return;
    }

    vector<Vertex<int> *> mst = primMPQ(&graph);

    for (auto v: graph.getVertexSet()) {
        v->setVisited(false);
    }
    Graph<int> mstGraph;
    for (auto v: mst) {
        mstGraph.addVertex(v->getInfo());
        auto ep = v->getPath();
        if (ep != nullptr) {
            if (!mstGraph.addBidirectionalEdge(ep->getOrig()->getInfo(), ep->getDest()->getInfo(), ep->getWeight())) {
                mstGraph.addVertex(ep->getOrig()->getInfo());
                mstGraph.addVertex(ep->getDest()->getInfo());
                mstGraph.addBidirectionalEdge(ep->getOrig()->getInfo(), ep->getDest()->getInfo(), ep->getWeight());
            }
        }
    }
    auto vector1 = mstGraph.dfs();
    for (auto s: vector1) {
        aproximationTour.push_back(graph.findVertex(s));
    }
    aproximationTour.push_back(startVertex);

    aproximationTourCost = calculateTourCost(aproximationTour, graph);
}

double TspManager::calculateTourCost(vector<Vertex<int> *> tour, Graph<int> &g) {
    double totalCost = 0.0;

    for (size_t i = 0; i < tour.size(); i++) {
        if (i > 0) {
            totalCost += getEdgeWeight(g, tour[i - 1]->getInfo(), tour[i]->getInfo());
        }
    }

    totalCost += getEdgeWeight(g, tour.back()->getInfo(), tour[0]->getInfo());

    return totalCost;
}

