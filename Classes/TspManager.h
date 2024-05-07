//
// Created by darksystem on 07-05-2024.
//

#ifndef PROJ2_TSPMANAGER_H
#define PROJ2_TSPMANAGER_H
#include "Data.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <climits>
#include <iomanip>

class TspManager {
public :
    TspManager();
    TspManager(const Data &d);


private:
    Graph<std::string> graph;
    std::unordered_map<int, std::pair<float, float>> nodesloc;
    std::unordered_map<int, std::string> labels;
};


#endif //PROJ2_TSPMANAGER_H
