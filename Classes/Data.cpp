#include "Data.h"
#include <iostream>
#include <sstream>



using namespace std;

Data::Data(const std::string &s) {
    if (s == "toy") {
        //readToyGraphs("../dataset/Toy_Graphs/...");
        readToyGraphs("../dataset/Toy-Graphs/tourism.csv");

    } else if (s == "extra") {
        readRealWorldGraphsVertex("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
        readExtraGraphsEdges("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
    } else if (s == "real") {
        readRealWorldGraphsVertex("../dataset/Real-world Graphs/graph1/edges.csv");
        readRealWorldGraphsEdges("../dataset/Real-world Graphs/graph1/edges.csv");
        readNodesOhioRizzGyatt("../dataset/Real-world Graphs/graph1/nodes.csv");
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
    }
}

