#pragma once
#include <eventlist.h>
#include <eigen3/Eigen/Dense>
#include <pipe.h>
// #include "Satellite.h"
#include "Node.h"

class LaserLink : public Pipe {
public:
    LaserLink(simtime_picosec delay, EventList &eventlist,const Node node1, const Node node2, bool isSatelliteLink);
    void doNextEvent(); // inherited from Pipe
    string nodename() const { return _nodename; }
    double getDistanceBetweenNodes(Eigen::Vector3d node1Position, Eigen::Vector3d node2Position) const;
    bool checkIsSatellite(){ return _isSatelliteLink; } //Check type of link
    virtual ~LaserLink(){};
private:
    typedef pair<simtime_picosec,Packet*> pktrecord_t;
    list<pktrecord_t> _inflight; // the packets in flight (or being serialized)
    string _nodename;
    Node _node1,_node2;
    bool _isSatelliteLink;
};



