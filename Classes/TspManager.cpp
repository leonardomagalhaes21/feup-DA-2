//
// Created by darksystem on 07-05-2024.
//

#include "TspManager.h"
#include <iostream>

using namespace std;
TspManager::TspManager() {
    graph = {};
}

TspManager::TspManager(const Data &d) {
    graph = d.getGraph();
    nodesloc = d.getNodesLoc();
    labels = d.getLabels();
}