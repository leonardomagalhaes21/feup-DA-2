#include "Data.h"
#include <iostream>
#include <sstream>

using namespace std;

Data::Data(const std::string &s) {
    if (s == "shipping") {
        readToyGraphs("../dataset/Toy-Graphs/shipping.csv");
    } else if (s == "stadiums") {
        readToyGraphs("../dataset/Toy-Graphs/stadiums.csv");
    } else if (s == "tourism") {
        readToyGraphsTourism("../dataset/Toy-Graphs/tourism.csv");

    } else if (s == "real1") {
        readNodes("../dataset/Real-world Graphs/graph1/nodes.csv");
        readGraphs("../dataset/Real-world Graphs/graph1/edges.csv");
        
    } else if (s == "real2") {
        readNodes("../dataset/Real-world Graphs/graph2/nodes.csv");
        readGraphs("../dataset/Real-world Graphs/graph2/edges.csv");

    } else if (s == "real3") {
        readNodes("../dataset/Real-world Graphs/graph3/nodes.csv");
        readGraphs("../dataset/Real-world Graphs/graph3/edges.csv");

    } else if (s == "25") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_25.csv");
    } else if (s == "50") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_50.csv");
    } else if (s == "100") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_100.csv");
    } else if (s == "200") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_200.csv");
    } else if (s == "300") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_300.csv");
    } else if (s == "400") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_400.csv");
    } else if (s == "500") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_500.csv");
    } else if (s == "600") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_600.csv");
    } else if (s == "700") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_700.csv");
    } else if (s == "800") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_800.csv");
    } else if (s == "900") {
        readNodesExtra("../dataset/Extra_Fully_Connected_Graphs/nodes.csv", stoi(s));
        readExtraGraphs("../dataset/Extra_Fully_Connected_Graphs/edges_900.csv");
    }
}

const std::unordered_map<int, std::pair<float, float>> &Data::getNodes() const {
    return this->nodesloc;
}

const Graph<std::string> &Data::getGraph() const {
    return this->graph;
}


void Data::readToyGraphsTourism(const std::string &filename) {
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

        graph.addVertex(vertex1);
        graph.addVertex(vertex2);
        graph.addEdge(vertex1, vertex2, distance);
        graph.addEdge(vertex2, vertex1, distance);
        labels.insert(std::make_pair(stoi(vertex1), label_origem));
        labels.insert(std::make_pair(stoi(vertex2), label_destino));
    }
}


void Data::readExtraGraphs(const std::string &filename) {

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

        graph.addEdge(vertex1, vertex2, distance);
        graph.addEdge(vertex2, vertex1, distance);
    }
}

void Data::readToyGraphs(const std::string &filename) {
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
        int vertex1;
        int vertex2;
        float distance;

        getline(linestream, temp, ',');
        vertex1 = stoi(temp);
        getline(linestream, temp, ',');
        vertex2 = stoi(temp);
        getline(linestream, temp, ',');
        distance = stof(temp);

        graph.addVertex(to_string(vertex1));
        graph.addVertex(to_string(vertex2));
        graph.addEdge(to_string(vertex1), to_string(vertex2), distance);
        graph.addEdge(to_string(vertex2), to_string(vertex1), distance);
    }

}

void Data::readGraphs(const std::string &filename) {
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
        int vertex1;
        int vertex2;
        float distance;

        getline(linestream, temp, ',');
        vertex1 = stoi(temp);
        getline(linestream, temp, ',');
        vertex2 = stoi(temp);
        getline(linestream, temp, ',');
        distance = stof(temp);

        graph.addEdge(to_string(vertex1), to_string(vertex2), distance);
        graph.addEdge(to_string(vertex2), to_string(vertex1), distance);
    }
}

void Data::readNodes(const std::string &filename) {
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

        graph.addVertex(to_string(id));
        nodesloc.insert(std::make_pair(id, std::make_pair(value, value2)));
    }

}

void Data::readNodesExtra(const std::string &filename, int limit) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "There was an error opening file " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line) && limit > 0) {
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

        graph.addVertex(to_string(id));
        nodesloc.insert(std::make_pair(id, std::make_pair(value, value2)));
        limit--;
    }
}

const unordered_map<int, std::pair<float, float>> Data::getNodesLoc() const {
    return nodesloc;
}

const unordered_map<int, std::string> Data::getLabels() const {
    return labels;
}


