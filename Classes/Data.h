#ifndef PROJECT_2_DATA_H
#define PROJECT_2_DATA_H

#include <unordered_map>
#include <string>
#include <fstream>
#include "Graph.h"

class Data {
public:
    Data(const std::string& s);
    const std::unordered_map<int, std::pair<float, float>> &getNodes() const;

    const Graph<std::string> &getGraph() const;
    void readExtraGraphsVertex(const std::string &filename);
    void readExtraGraphsEdges(const std::string &filename);
    void readRealWorldGraphsVertex(const std::string &filename);
    void readRealWorldGraphsEdges(const std::string &filename);
    void readNodesOhioRizzGyatt(const std::string &filename);
private:
    Graph<std::string> graph;
    std::unordered_map<int, std::pair<float, float>> nodes;
    void readToyGraphs(const std::string &filename);

};

#endif //PROJECT_2_DATA_H
