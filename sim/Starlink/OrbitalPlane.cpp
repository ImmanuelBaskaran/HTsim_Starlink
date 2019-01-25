#include "OrbitalPlane.h"

OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset)
: _id(id), _raan(raan), _satAltitude(satAltitude), _inclination(inclination), _firstSatOffset(firstSatOffset) {
    _satellites = new Satellite[SATS_PER_PLANE];
    initSatellites();
}

OrbitalPlane::initSatellites() {
    for (int i = 0; i < SATS_PER_PLANE; i++) {
        int satId = SATS_PER_PLANE * (_id - 1) + i + 1;
        _satellites[i] = new Satellite(satId, _firstSatOffset);
    }
}

OrbitalPlane::satIdToIndex(int satId) {
    return satId - 1 - SATS_PER_PLANE * (_id - 1);
}

Vector3 OrbitalPlane::getPosForSat(int satId, simtime_picosec currentTime) {
    Satellite* sat = _satellites[satIdToIndex(satId)];
    Vector3 startPosition(EARTH_RADIUS + _satAltitude, 0.0, 0.0);
    AngleAxis<double> startRot(_raan, Vector3(0, 0, 1));

    // For 1st satellite in 1st plane, coords are (Earth radius + altitude, 0, 0)
    // 
    AngleAxis<double> rot1(sat->getAnomaly(currentTime), Vector3(0, 0, 1));
    AngleAxis<double> rot2(_inclination, Vector3(1, 0, 0));
    AngleAxis<double> rot3(_raan, Vector3(0, 1, 0));

    return startPosition * startRot * rot1 * rot2 * rot3;
}
