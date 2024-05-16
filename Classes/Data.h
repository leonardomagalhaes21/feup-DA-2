#ifndef PROJECT_2_DATA_H
#define PROJECT_2_DATA_H

#include <unordered_map>
#include <string>
#include <fstream>
#include "Graph.h"

class Data {
public:
    Data(const std::string &s);

    const std::unordered_map<int, std::pair<float, float>> &getNodes() const;

    const Graph<int> &getGraph() const;


    void readExtraGraphs(const std::string &filename);

    void readToyGraphs(const std::string &filename);

    void readGraphs(const std::string &filename);

    void readNodes(const std::string &filename);

    void readToyGraphsTourism(const std::string &filename);

    void readNodesExtra(const std::string &filename, int limit);


    const std::unordered_map<int, std::pair<float, float>> getNodesLoc() const;

    const std::unordered_map<int, std::string> getLabels() const;


private:
    Graph<int> graph;
    std::unordered_map<int, std::pair<float, float>> nodesloc;
    std::unordered_map<int, std::string> labels;



};

#endif //PROJECT_2_DATA_H
