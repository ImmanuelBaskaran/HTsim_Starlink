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
    vector<Satellite> getSatellitesInRange(vector<Satellite> positionMatrix);
    bool isSatelliteInRange(Satellite satellite);
private:
    double lat,lon;
};


#endif //SIM_GROUNDSTATION_H
