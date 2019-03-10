#include "OrbitalPlane.h"
#include "Satellite.h"
#include <Eigen/Geometry>

OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset)
: _id(id), _raan(raan), _satAltitude(satAltitude), _inclination(inclination), _firstSatOffset(firstSatOffset) {
    for (int i = 0; i < SATS_PER_PLANE; i++) {
        int satId = SATS_PER_PLANE * (_id - 1) + i + 1;
        _satellites[i] = new Satellite(satId, _firstSatOffset, inclination, raan, satAltitude);
    }
}

int OrbitalPlane::satIdToIndex(int satId) const {
    return satId - 1 - SATS_PER_PLANE * (_id - 1);
}

Satellite* OrbitalPlane::getSatByID(int satId) const {
    return _satellites[satIdToIndex(satId)];
}
