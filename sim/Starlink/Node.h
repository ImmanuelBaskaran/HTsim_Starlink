#ifndef SIM_NODE_H
#define SIM_NODE_H

#include <Eigen/Dense>

class Node  {
private:
    int _id;
public:
    Node(int id) : _id(id) { }
    inline int getId() const { return _id; }
    virtual Eigen::Vector3d getPosition(simtime_picosec currentTime) const;
    virtual PacketSink* getPacketSink();
};

#endif SIM_NODE_H