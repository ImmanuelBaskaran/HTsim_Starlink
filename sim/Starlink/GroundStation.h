#pragma once

#include "network.h"
#include "cbr.h"
#include "Satellite.h"
#include <Eigen/Geometry>

class GroundStation: public CbrSink, public CbrSrc {
public:
    GroundStation(EventList &eventlist1,double lat, double lon, int id);
    // std::vector<Satellite*> getSatellitesInRange(const Constellation& constellation, simtime_picosec currentTime);
    bool isSatelliteInRange(const Satellite& sat, simtime_picosec currentTime);
    Eigen::Vector3d getPosition(simtime_picosec currentTime) const;
    inline int getId() const { return _id; }
private:
    int _id;
    double _lat, _lon;
    std::vector<Satellite*> _satsInRange;
};