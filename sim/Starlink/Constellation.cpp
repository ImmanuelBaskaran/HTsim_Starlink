//
// Created by metal on 25/02/19.
//

#include "Constellation.h"
#include "Satellite.h"
#include "OrbitalPlane.h"

double toRadians(double degrees){
    return (degrees * (M_PI/180));
}

Constellation::Constellation(EventList& eventlist, const string& name): EventSource(eventlist,name) {
    int id = 1;
    for (int i = 0; i < 24; i++) {
        _planes[i] = new OrbitalPlane(i + 1, i * toRadians(15), toRadians(53.0), 550000, i * toRadians(5.5));
        for (int j = 0; j < SATS_PER_PLANE; j++) {
            Eigen::Vector3d pos = _planes[i]->getPosForSat(id++, 0);
            printf("Plane %d, Sat %d: %f %f %f\n", i, j, pos.x(), pos.y(), pos.z());
        }
    }
}

Satellite* Constellation::getSatByID(int satId) {
    return _planes[satId/66]->getSatByID(satId%66);
}


void
Constellation::doNextEvent() {
    eventlist().sourceIsPendingRel(*this, timeFromMs(10));
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < SATS_PER_PLANE; j++) {
           Eigen::Vector3d newPos = _planes[i]->getPosForSat(j,eventlist().now());
            _planes[i]->getSatByID(j)->setPosition(newPos);
        }
    }
}
