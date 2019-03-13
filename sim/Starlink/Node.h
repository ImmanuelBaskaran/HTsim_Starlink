#ifndef SIM_NODE_H
#define SIM_NODE_H

#include <Eigen/Dense>
#include "network.h"

class Node  {
private:
    int _id;
public:
    Node(int id) : _id(id) { }
    virtual ~Node() { }
    inline int getId() const { return _id; }
    virtual Eigen::Vector3d getPosition(simtime_picosec currentTime) const = 0;
    virtual PacketSink* getPacketSink() = 0;
};

#endif