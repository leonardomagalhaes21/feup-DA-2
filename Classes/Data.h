#ifndef PROJECT_2_DATA_H
#define PROJECT_2_DATA_H

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Graph.h"

class Data {
public:
    /**
     * @brief Constructor that initializes the data from the given system
     * @param s String indicating the system to be used
     */
    Data(const std::string &s);

    /**
     * @brief Gets the nodes
     * @return Map of nodes
     */
    const std::unordered_map<int, std::pair<float, float>> &getNodes() const;

    /**
     * @brief Gets the graph
     * @return Graph
     */
    const Graph<int> &getGraph() const;

    /**
     * @brief Reads the extra graphs from the given filename
     * @param filename String indicating the filename
     */
    void readExtraGraphs(const std::string &filename);

    /**
     * @brief Reads the toy graphs from the given filename
     * @param filename String indicating the filename
     */
    void readToyGraphs(const std::string &filename);

    /**
     * @brief Reads the graphs from the given filename
     * @param filename String indicating the filename
     */
    void readGraphs(const std::string &filename);

    /**
     * @brief Reads the nodes from the given filename
     * @param filename String indicating the filename
     */
    void readNodes(const std::string &filename);

    /**
     * @brief Reads the toy graphs for tourism from the given filename
     * @param filename String indicating the filename
     */
    void readToyGraphsTourism(const std::string &filename);

    /**
     * @brief Reads the nodes from the given filename with a limit
     * @param filename String indicating the filename
     * @param limit Integer indicating the limit
     */
    void readNodesExtra(const std::string &filename, int limit);

    /**
     * @brief Gets the nodes location
     * @return Map of nodes location
     */
    std::unordered_map<int, std::pair<float, float>> getNodesLoc() const;

    /**
     * @brief Gets the labels
     * @return Map of labels
     */
    std::unordered_map<int, std::string> getLabels() const;


private:
    Graph<int> graph;
    std::unordered_map<int, std::pair<float, float>> nodesloc;
    std::unordered_map<int, std::string> labels;



};

#endif //PROJECT_2_DATA_H
