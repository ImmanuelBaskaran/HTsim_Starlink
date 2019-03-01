#include "OrbitalPlane.h"
#include "Satellite.h"
#include <Eigen/Geometry>

using namespace Eigen;

OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset)
: _id(id), _raan(raan), _satAltitude(satAltitude), _inclination(inclination), _firstSatOffset(firstSatOffset) {
    // _planeOffset = ((id - 1) / 24.0) * 2.0 * M_PI;
    for (int i = 0; i < SATS_PER_PLANE; i++) {
        int satId = SATS_PER_PLANE * (_id - 1) + i + 1;
        _satellites[i] = new Satellite(satId, _firstSatOffset);
        Eigen::Vector3d pos = getPosForSat(satId,0);
        _satellites[i]->setPosition(pos);
    }
}

int OrbitalPlane::satIdToIndex(int satId) const {
    return satId - 1 - SATS_PER_PLANE * (_id - 1);
}

Satellite* OrbitalPlane::getSatByID(int satId) const {
    return _satellites[(satId)];
}

Vector3d OrbitalPlane::getPosForSat(int satId, simtime_picosec currentTime) const {
    Satellite* sat = _satellites[satIdToIndex(satId)];
    Vector3d startPosition(EARTH_RADIUS + _satAltitude, 0.0, 0.0);

    Vector3d result;
    // AngleAxis<double> m1(_planeOffset, Vector3d(0.0, 0.0, 1.0));
    double anomaly = sat->getAnomaly(currentTime);
    AngleAxis<double> m2(anomaly, Vector3d(0.0, 0.0, 1.0));
    AngleAxis<double> m3( M_PI/2 - _inclination, Vector3d(1.0, 0.0, 0.0));
    AngleAxis<double> m4(_raan, Vector3d(0.0, 1.0, 0.0));
    result = m4*m3*m2*startPosition;
    return result;

    // Vector3d result;
    // AngleAxis<double> m1(_planeOffset, Vector3d(1.0, 0.0, 0.0));
    // AngleAxis<double> m2(sat->getAnomaly(currentTime), Vector3d(1.0, 0.0, 0.0));
    // AngleAxis<double> m3( M_PI/2 - _inclination, Vector3d(0.0, 1.0, 0.0));
    // AngleAxis<double> m4(_raan, Vector3d(0.0, 0.0, 1.0));
    // result = m4*m3*m2*m1*startPosition;
    // return result;

}
