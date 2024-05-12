#include "Data.h"
#include <iostream>
#include <sstream>



using namespace std;

Data::Data(const std::string &s) {
    if (s == "tourism") {
        readToyGraphs("../dataset/Toy-Graphs/tourism.csv");
    } else if (s == "stadiums") {
        readToyGraphs("../dataset/Toy-Graphs/stadiums.csv");
    } else if (s == "tourism") {
        readToyGraphs("../dataset/Toy-Graphs/tourism.csv");

    } else if (s == "extra") {
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
    } else if (s == "real1") {
        readRealWorldGraphsVertex("../dataset/Real-world Graphs/graph1/edges.csv");
        readRealWorldGraphsEdges("../dataset/Real-world Graphs/graph1/edges.csv");
        readNodesOhioRizzGyatt("../dataset/Real-world Graphs/graph1/nodes.csv");
    }
    else if (s == "real2") {
        readRealWorldGraphsVertex("../dataset/Real-world Graphs/graph2/edges.csv");
        readRealWorldGraphsEdges("../dataset/Real-world Graphs/graph2/edges.csv");
        readNodesOhioRizzGyatt("../dataset/Real-world Graphs/graph2/nodes.csv");
    }
    else if (s == "real3") {
        readRealWorldGraphsVertex("../dataset/Real-world Graphs/graph3/edges.csv");
        readRealWorldGraphsEdges("../dataset/Real-world Graphs/graph3/edges.csv");
        readNodesOhioRizzGyatt("../dataset/Real-world Graphs/graph3/nodes.csv");
    }
    else if (s == "25"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_25.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_25.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_25.csv");
    }
    else if (s == "50"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_50.csv");
    }
    else if (s == "100"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_100.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_100.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_100.csv");
    }
    else if (s == "200"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_200.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_200.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_200.csv");
    }
    else if (s == "300"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_300.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_300.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_300.csv");
    }
    else if (s == "400"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_400.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_400.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_400.csv");
    }
    else if (s == "500"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_500.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_500.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_500.csv");
    }
    else if (s == "600"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_600.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_600.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_600.csv");
    }
    else if (s == "700"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_700.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_700.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_700.csv");
    }
    else if (s == "800"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_800.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_800.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_800.csv");
    }
    else if (s == "900"){
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_900.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_900.csv");
        readNodesOhioRizzGyatt("../dataset/Extra_Fully_Connected_Graphs/nodes_900.csv");
    }
}

const std::unordered_map<int, std::pair<float, float>> &Data::getNodes() const {
    return this->nodesloc;
}

const Graph<std::string> &Data::getGraph() const {
    return this->graph;
}

void Data::readToyGraphs(const std::string &filename) {
    //readRealWorldGraphsVertex(filename);
    //readToyGraphsEdges(filename);
//    readToyGraphsTourismVertex(filename);
    readToyGraphsTourism(filename);
}

void Data::readToyGraphsTourism(const std::string &filename) {
    readRealWorldGraphsVertex(filename);
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream linestream(line);
        string temp;
        string vertex1, vertex2, label_origem, label_destino;
        float distance;

        getline(linestream, vertex1, ',');
        getline(linestream, vertex2, ',');
        getline(linestream, temp, ',');
        distance = stof(temp);
        getline(linestream, label_origem, ',');
        getline(linestream, label_destino, ',');

        graph.addEdge(vertex1, vertex2, distance);
        graph.addEdge(vertex2, vertex1, distance);
        labels.insert(std::make_pair(stoi(vertex1), label_origem));
        labels.insert(std::make_pair(stoi(vertex2), label_destino));

    }
}

//void Data::readToyGraphsTourismVertex(const string &filename) {
//
//    ifstream file(filename);
//
//    if (!file.is_open()) {
//        cerr << "There was an error opening file " << filename << endl;
//        return;
//    }
//
//    string line;
//    getline(file, line);
//    while (getline(file, line)) {
//        stringstream linestream(line);
//        string temp;
//        getline(linestream, temp, ',');
//        graph.addVertex(temp);
//    }
//
//}
//void Data::readExtraGraphsVertex(const std::string &filename) {
//    ifstream file(filename);
//
//    if (!file.is_open()) {
//        cerr << "There was an error opening file " << filename << endl;
//        return;
//    }
//
//    string line;
//    while (getline(file, line)) {
//        stringstream linestream(line);
//        string temp;
//        getline(linestream, temp, ',');
//        graph.addVertex(temp);
//    }
//}
void Data::readExtraGraphsEdges(const std::string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream linestream(line);
        string temp;
        string vertex1, vertex2;
        float distance;

        getline(linestream, vertex1, ',');
        getline(linestream, vertex2, ',');
        getline(linestream, temp, ',');
        distance = stof(temp);

        graph.addEdge(vertex1, vertex2,distance);
        graph.addEdge(vertex2, vertex1,distance);
    }
}
void Data::readRealWorldGraphsVertex(const std::string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream linestream(line);
        string temp;
        getline(linestream, temp, ',');
        graph.addVertex(temp);
    }
}
void Data::readRealWorldGraphsEdges(const std::string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream linestream(line);
        string temp;
        string vertex1, vertex2;
        float distance;

        getline(linestream, vertex1, ',');
        getline(linestream, vertex2, ',');
        getline(linestream, temp, ',');
        distance = stof(temp);

        graph.addEdge(vertex1, vertex2,distance);
        graph.addEdge(vertex2, vertex1,distance);
    }
}

void Data::readNodesOhioRizzGyatt(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream linestream(line);
        string temp;
        int id;
        float value;
        float value2;

        getline(linestream, temp, ',');
        id = stoi(temp);
        getline(linestream, temp, ',');
        value = stof(temp);
        getline(linestream, temp, ',');
        value2 = stof(temp);

        nodesloc.insert(std::make_pair(id, std::make_pair(value, value2)));
    }

}

void Data::readToyGraphsEdges(const string &filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream linestream(line);
        string temp;
        string vertex1, vertex2;
        float distance;

        getline(linestream, vertex1, ',');
        getline(linestream, vertex2, ',');
        getline(linestream, temp, ',');
        distance = stof(temp);

        graph.addEdge(vertex1, vertex2, distance);
        graph.addEdge(vertex2, vertex1,distance);
    }
}

const unordered_map<int, std::pair<float, float>> Data::getNodesLoc() const{
    return nodesloc;
}

const unordered_map<int, std::string> Data::getLabels() const {
    return labels;
}

