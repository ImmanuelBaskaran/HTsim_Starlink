#pragma once
#define SIM_LASERLINK_H


#include <eventlist.h>
#include <eigen3/Eigen/Dense>
#include <pipe.h>
#include "Satellite.h"



class LaserLink : public Pipe {
public:
    LaserLink(simtime_picosec delay, EventList &eventlist, const Satellite& sat1, const Satellite& sat2);
    void doNextEvent(); // inherited from Pipe
    string nodename() const { return _nodename; }
    double getDistanceBetweenSatellitePair(const Satellite& satellite, const Satellite& satellite2, simtime_picosec currentTime) const;
    virtual ~LaserLink(){};
private:
    typedef pair<simtime_picosec,Packet*> pktrecord_t;
    list<pktrecord_t> _inflight; // the packets in flight (or being serialized)
    string _nodename;
    Satellite _sat1,_sat2;
};



