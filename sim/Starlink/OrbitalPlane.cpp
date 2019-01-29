#include "OrbitalPlane.h"
#include "Satellite.h"
#include <Eigen/Geometry>

OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset)
: _id(id), _raan(raan), _satAltitude(satAltitude), _inclination(inclination), _firstSatOffset(firstSatOffset) {
    //_satellites = new Satellite*[SATS_PER_PLANE];
    initSatellites();
}

void OrbitalPlane::initSatellites() {
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

    Transform t(AngleAxis<double>(_raan, Vector3d(0.0, 0.0, 1.0));)

    t.rotate(AngleAxis<double>(sat->getAnomaly(currentTime), Vector3d(0, 0, 1)));
    t.rotate(AngleAxis<double>(_inclination, Vector3d(1, 0, 0)));
    t.rotate(AngleAxis<double>(_raan, Vector3d(0, 1, 0)));
    return t * startPosition;
}
