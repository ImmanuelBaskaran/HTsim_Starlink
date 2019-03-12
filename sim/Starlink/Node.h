//
// Created by metal on 11/03/19.
//

#ifndef SIM_NODE_H
#define SIM_NODE_H


#include "network.h"
#include "cbr.h"

class Node  {

    int _id;
public:
    Node(int id) : _id(id) {
        _id = id;
    }

public:
    inline int getId() const { return _id; }

    Eigen::Vector3d getPosition(simtime_picosec currentTime) {
        return Eigen::Vector3d();
    }
};


#endif SIM_NODE_H
