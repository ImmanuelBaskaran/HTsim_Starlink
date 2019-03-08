//
// Created by metal on 25/01/19.
//

#ifndef SIM_GROUNDSTATION_H
#define SIM_GROUNDSTATION_H

#include "network.h"
#include "cbr.h"
#include "Satellite.h"
#include <Eigen/Geometry>


class GroundStation: public CbrSink, public CbrSrc {
public:
    GroundStation(EventList &eventlist1,double lat, double lon, int id);
    std::vector<Satellite*> getSatellitesInRange(const Constellation& constellation, simtime_picosec currentTime);
    bool isSatelliteInRange(const Satellite& sat, simtime_picosec currentTime);
    Eigen::Vector3d getPosition();
    int getId() const;
private:
    int _id;
    double _lat, _lon;
    std::vector<Satellite*> _satsInRange;
};


#endif //SIM_GROUNDSTATION_H
