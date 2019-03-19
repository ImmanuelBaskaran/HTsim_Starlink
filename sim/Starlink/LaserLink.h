#pragma once
#include <eventlist.h>
#include <eigen3/Eigen/Dense>
#include <pipe.h>
#include "Node.h"

class LaserLink : public Pipe {
public:
    LaserLink(simtime_picosec delay, EventList &eventlist, const Node& node1,
              const Node& node2, bool isSatelliteLink);
    void doNextEvent() override;
    void receivePacket(Packet& pkt) override;
    inline bool checkIsSatellite() const { return _isSatelliteLink; } //Check type of link
    virtual ~LaserLink(){};
private:
    list<pktrecord_t> _inflight; // the packets in flight (or being serialized)
    const Node& _node1;
    const Node& _node2;
    bool _isSatelliteLink;
};



