#include "OrbitalPlane.h"
#include "Satellite.h"
#include <Eigen/Geometry>

using namespace Eigen;

OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset)
: _id(id), _raan(raan), _satAltitude(satAltitude), _inclination(inclination), _firstSatOffset(firstSatOffset) {
    _planeOffset = ((id - 1) / 24.0) * 2.0 * M_PI;
    for (int i = 0; i < SATS_PER_PLANE; i++) {
        int satId = SATS_PER_PLANE * (_id - 1) + i + 1;
        _satellites[i] = new Satellite(satId, _firstSatOffset);
        Eigen::Vector3f pos = getPosForSat(satId,0);
        _satellites[i]->setPosition(pos);
    }
}

int OrbitalPlane::satIdToIndex(int satId) {
    return satId - 1 - SATS_PER_PLANE * (_id - 1);
}

Vector3f const OrbitalPlane::getPosForSat(int satId, simtime_picosec currentTime) {
    Satellite* sat = _satellites[satIdToIndex(satId)];
    Vector3f startPosition(EARTH_RADIUS + _satAltitude, 0.0, 0.0);

    Vector3f result;
    AngleAxis<float> m1(_planeOffset, Vector3f(0.0, 0.0, 1.0));
    AngleAxis<float> m2(sat->getAnomaly(currentTime), Vector3f(0.0, 0.0, 1.0));
    AngleAxis<float> m3( M_PI/2 - _inclination, Vector3f(1.0, 0.0, 0.0));
    AngleAxis<float> m4(_raan, Vector3f(0.0, 1.0, 0.0));
    result = m4*m3*m2*m1*startPosition;
    return result;
}

Satellite* OrbitalPlane::getSatByID(int satId) {

    return _satellites[(satId)];
}
