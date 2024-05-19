#ifndef PROJ2_TSPMANAGER_H
#define PROJ2_TSPMANAGER_H

#include "Data.h"
#include <iostream>
#include <unordered_set>
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
    /**
     * @brief Default constructor
     * @details Time complexity: O(1)
     */
    TspManager();

    /**
     * @brief Constructor that initializes the graph, nodes location and labels from the given data
     * @details Time complexity: O(1)
     * @param d Data object containing the graph, nodes location and labels
     */
    TspManager(const Data &d);

    /**
     * @brief Executes the backtracking algorithm for the TSP problem
     * @details Time complexity: O(n!), where n is the number of vertices in the graph
     */
    void tspBacktracking();

    /**
     * @brief Executes the Prim's algorithm for the TSP problem
     * @details Time complexity: O(ElogV), where E is the number of edges and V is the number of vertices in the graph
     * @param incompleteGraph Boolean indicating if the graph is incomplete
     */
    void tspPrim(bool incompleteGraph);

    /**
     * @brief Prints the network information
     * @details Time complexity: O(V), where V is the number of vertices in the graph
     * @param system String indicating the system type
     */
    void printNetworkInfo(const std::string &system);

    /**
     * @brief Executes the triangular heuristic algorithm for the TSP problem with user input
     * @details Time complexity: O(V^2), where V is the number of vertices in the graph
     */
    void tspTriangularHeuristicInput();

    /**
     * @brief Compares the performance of the backtracking, triangular heuristic and Prim's algorithms
     */
    void compareAlgorithmsPerformance();

    /**
     * @brief Executes the Kruskal's algorithm for the real world problem
     * @details Time complexity: O(ElogE), where E is the number of edges in the graph
     */
    void kruskalRealWorld();

    /**
     * @brief Executes the triangular heuristic algorithm for the TSP problem with alternative user input
     * @details Time complexity: O(V^2), where V is the number of vertices in the graph
     */
    void tspTriangularHeuristicAlternativeInput();

private:
    Graph<int> graph;
    std::unordered_map<int, std::pair<float, float>> nodesloc;
    std::unordered_map<int, std::string> labels;

    /**
     * @brief Executes the backtracking method for the TSP problem
     * @details Time complexity: O(n!), where n is the number of vertices in the graph
     * @param bestTour Vector to store the best tour
     * @param minTourCost Double to store the minimum tour cost
     */
    void tspBacktrackingMethod(std::vector<int> &bestTour, double &minTourCost);

    /**
     * @brief Recursive function for the TSP problem
     * @details Time complexity: O(n!), where n is the number of vertices in the graph
     * @param tour Vector to store the current tour
     * @param visited Vector to store the visited nodes
     * @param currentCost Double to store the current cost
     * @param minCost Double to store the minimum cost
     * @param bestTour Vector to store the best tour
     */
    void tspRec(std::vector<int> &tour, std::vector<bool> &visited, double currentCost, double &minCost, std::vector<int> &bestTour);

    /**
     * @brief Checks if an edge exists between two vertices
     * @details Time complexity: O(E), where E is the number of edges in the graph
     * @param pVertex Pointer to the first vertex
     * @param pVertex1 Pointer to the second vertex
     * @return True if an edge exists, false otherwise
     */
    static bool hasEdge(Vertex<int> *pVertex, Vertex<int> *pVertex1);

    /**
     * @brief Gets the weight of an edge in the graph
     * @details Time complexity: O(E), where E is the number of edges in the graph
     * @param graph Reference to the graph
     * @param node Integer representing the node
     * @param i Integer representing the other node
     * @return The weight of the edge
     */
    static double getEdgeWeight(Graph<int>& graph, int node, int i);

    /**
     * @brief Completes the graph
     * @details Time complexity: O(V^2), where V is the number of vertices in the graph
     * @param graphCopy Copy of the graph to be completed
     */
    void completeGraph(Graph<int> graphCopy);

    /**
     * @brief Gets the latitude of a vertex
     * @details Time complexity: O(1)
     * @param vertex Pointer to the vertex
     * @return The latitude of the vertex
     */
    float getLatitude(Vertex<int> *vertex) const;

    /**
     * @brief Gets the longitude of a vertex
     * @details Time complexity: O(1)
     * @param vertex Pointer to the vertex
     * @return The longitude of the vertex
     */
    float getLongitude(Vertex<int> *vertex) const;

    /**
     * @brief Calculates the haversine distance between two points
     * @details Time complexity: O(1)
     * @param lat1 Latitude of the first point
     * @param lon1 Longitude of the first point
     * @param lat2 Latitude of the second point
     * @param lon2 Longitude of the second point
     * @return The haversine distance between the two points
     */
    static double haversineDistance(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Executes the triangular heuristic method for the TSP problem
     * @details Time complexity: O(V^2), where V is the number of vertices in the graph
     * @param bestTour Vector to store the best tour
     * @param startNode Integer representing the start node
     */
    void tspTriangularHeuristicMethod(std::vector<int> &bestTour, int startNode);

    /**
     * @brief Executes the Prim's algorithm for the TSP problem
     * @details Time complexity: O(ElogV), where E is the number of edges and V is the number of vertices in the graph
     * @param g Pointer to the graph
     * @return Vector of pointers to the vertices
     */
    static std::vector<Vertex<int> *> primMPQ(Graph<int> *g);

    /**
     * @brief Copies a graph
     * @details Time complexity: O(V+E), where V is the number of vertices and E is the number of edges in the graph
     * @param originalGraph Reference to the original graph
     * @return The copied graph
     */
    static Graph<int> copyGraph(const Graph<int> &originalGraph);

    /**
     * @brief Executes the Prim's method for the TSP problem
     * @details Time complexity: O(ElogV), where E is the number of edges and V is the number of vertices in the graph
     * @param graphTemp Reference to the temporary graph
     * @param startVertex Pointer to the start vertex
     * @param shortestPathEdges Vector to store the shortest path edges
     */
    static void tspPrimMethod(const Graph<int> &graphTemp, Vertex<int> *startVertex, std::vector<Edge<int> *> &shortestPathEdges);

    /**
     * @brief Executes the triangular heuristic approximation for the TSP problem
     * @details Time complexity: O(V^2), where V is the number of vertices in the graph
     * @param startNodeId Integer representing the start node id
     * @param aproximationTour Vector to store the approximation tour
     * @param aproximationTourCost Double to store the approximation tour cost
     */
    void triangularHeuristicAproximation(int startNodeId, std::vector<Vertex<int>*> &aproximationTour, double &aproximationTourCost);

    /**
     * @brief Calculates the tour cost
     * @details Time complexity: O(V), where V is the number of vertices in the graph
     * @param tour Vector representing the tour
     * @param g Reference to the graph
     * @return The cost of the tour
     */
    static double calculateTourCost(std::vector<Vertex<int> *> tour, Graph<int> &g);

};


#endif //PROJ2_TSPMANAGER_H
