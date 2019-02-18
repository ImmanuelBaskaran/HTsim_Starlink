
#define SIM_LASERLINK_H


#include <eventlist.h>
#include <eigen3/Eigen/Dense>
#include <pipe.h>
#include "Satellite.h"



class LaserLink : public Pipe {
public:
    LaserLink(simtime_picosec delay1, EventList &eventlist1, simtime_picosec delay, EventList &eventlist);
    void doNextEvent(); // inherited from Pipe
    simtime_picosec delay() { return _delay; }
    const string& nodename() { return _nodename; }
    Eigen::Vector3f getSatellitePosition(Satellite satellite);
    double getDistanceBetweenSatellitePair(Satellite satellite,Satellite satellite2);
private:
    simtime_picosec _delay;
    typedef pair<simtime_picosec,Packet*> pktrecord_t;
    list<pktrecord_t> _inflight; // the packets in flight (or being serialized)
    string _nodename;
};



