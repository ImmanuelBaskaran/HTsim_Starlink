#include "OrbitalPlane.h"
#include "Satellite.h"
#include <Eigen/Geometry>

OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset)
: _id(id), _raan(raan), _satAltitude(satAltitude), _inclination(inclination), _firstSatOffset(firstSatOffset) {
    _planeOffset = ((id - 1) / 24.0) * 2.0 * M_PI;
    for (int i = 0; i < SATS_PER_PLANE; i++) {
        int satId = SATS_PER_PLANE * (_id - 1) + i + 1;
        _satellites[i] = new Satellite(satId, _firstSatOffset);
    }
}

int OrbitalPlane::satIdToIndex(int satId) {
    return satId - 1 - SATS_PER_PLANE * (_id - 1);
}

Vector3d const OrbitalPlane::getPosForSat(int satId, simtime_picosec currentTime) {
    Satellite* sat = _satellites[satIdToIndex(satId)];
    Vector3d startPosition(EARTH_RADIUS + _satAltitude, 0.0, 0.0);

    Vector3d result;
    AngleAxis<double> m1(_planeOffset, Vector3d(0.0, 0.0, 1.0));
    AngleAxis<double> m2(sat->getAnomaly(currentTime), Vector3d(0.0, 0.0, 1.0));
    AngleAxis<double> m3( M_PI/2 - _inclination, Vector3d(1.0, 0.0, 0.0));
    AngleAxis<double> m4(_raan, Vector3d(0.0, 1.0, 0.0));
    result = m4*m3*m2*m1*startPosition;
    return result;
}