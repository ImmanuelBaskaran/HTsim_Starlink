//
// Created by metal on 25/01/19.
//

#ifndef SIM_GROUNDSTATION_H
#define SIM_GROUNDSTATION_H

#include "network.h"
#include "cbr.h"
#include "Satellite.h"


class GroundStation: public CbrSink, public CbrSrc {
public:
    GroundStation(EventList &eventlist1,double lat, double lon);
    std::vector<Eigen::Vector3d> GroundStation::getSatellitesInRange();
    bool isSatelliteInRange(Eigen::Vector3d satPos, double alt);
    double GroundStation::toRadians(double degrees);
private:
    double _lat, _lon;
};


#endif //SIM_GROUNDSTATION_H
