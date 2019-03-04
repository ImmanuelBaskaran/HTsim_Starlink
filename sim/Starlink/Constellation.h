//
// Created by metal on 25/02/19.
//

#ifndef SIM_CONSTELLATION_H
#define SIM_CONSTELLATION_H


#include "Satellite.h"
#include "OrbitalPlane.h"

class Constellation : public EventSource{
    private:
        OrbitalPlane* _planes[24];
    public:
        Constellation(EventList& eventlist, const string& name);
        void doNextEvent();
        Satellite* getSatByID(int satId);
        Eigen::Vector3d getSatPosByIDAtTime(int satId,simtime_picosec time);
};


#endif //SIM_CONSTELLATION_H
