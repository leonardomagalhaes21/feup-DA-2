//
// Created by darksystem on 12-05-2024.
//

#ifndef PROJ2_SEGMENT_H
#define PROJ2_SEGMENT_H
#include <iostream>
using namespace std;

class Segment {
public:
    // Define constructor and necessary member functions
    Segment(string _nodeA, string _nodeB, double _cost);

private:

    string getNodeA() const;

    string getNodeB() const;

    double getCost() const;

    string nodeA;
    string nodeB;
    double cost;
};



#endif //PROJ2_SEGMENT_H
