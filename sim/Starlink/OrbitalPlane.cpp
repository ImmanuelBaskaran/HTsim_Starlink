#include "OrbitalPlane.h"
#include "Satellite.h"
#include "eigen3/Eigen/Dense"


OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset)
: _id(id), _raan(raan), _satAltitude(satAltitude), _inclination(inclination), _firstSatOffset(firstSatOffset) {
    _satellites = new Satellite[SATS_PER_PLANE];
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

const Eigen::Vector3d OrbitalPlane::getPosForSat(int satId, simtime_picosec currentTime) {
    Satellite* sat = _satellites[satIdToIndex(satId)];
    Eigen::Vector3d startPosition(EARTH_RADIUS + _satAltitude, 0.0, 0.0);
    Eigen::AngleAxis<double> startRot(_raan, Eigen::Vector3d(0, 0, 1));

    // For 1st satellite in 1st plane, coords are (Earth radius + altitude, 0, 0)
    // 
    Eigen::AngleAxis<double> rot1(sat->getAnomaly(currentTime), Eigen::Vector3d(0, 0, 1));
    Eigen::AngleAxis<double> rot2(_inclination, Eigen::Vector3d(1, 0, 0));
    Eigen::AngleAxis<double> rot3(_raan, Eigen::Vector3d(0, 1, 0));

    return startPosition * startRot * rot1 * rot2 * rot3;
}
