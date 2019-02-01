//
// Created by metal on 25/01/19.
//

#ifndef SIM_GROUNDSTATION_H
#define SIM_GROUNDSTATION_H

#include <eigen3/Eigen/Dense>
#include "network.h"
#include "Satellite.h"


class GroundStation: public PacketSink {
public:
    GroundStation(double lat, double lon);
    vector<Satellite> getSatellitesInRange(vector<Satellite> positionMatrix);
    bool isSatelliteInRange(Satellite satellite);
private:
    double lat,lon;
};


#endif //SIM_GROUNDSTATION_H
