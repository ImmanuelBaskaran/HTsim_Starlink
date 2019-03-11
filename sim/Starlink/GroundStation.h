#pragma once

#include "network.h"
#include "cbr.h"
#include "Satellite.h"
#include "Node.h"

class GroundStation: public CbrSink, public CbrSrc, public Node {
public:
    GroundStation(EventList &eventlist1,double lat, double lon, int id);
    // std::vector<Satellite*> getSatellitesInRange(const Constellation& constellation, simtime_picosec currentTime);
    bool isSatelliteInRange(const Satellite& sat, simtime_picosec currentTime);
    Eigen::Vector3d getPosition(simtime_picosec currentTime);
    void send_packet();

private:
    double _lat, _lon;
    std::vector<Satellite*> _satsInRange;
};