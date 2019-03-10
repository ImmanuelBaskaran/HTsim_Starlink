#include "Satellite.h"
#include "StarlinkLib.h"

Satellite::Satellite(int id, double offset, double planeInclination, double raan, double altitude)
: _id(id), _planeInclination(planeInclination), _raan(raan), _altitude(altitude) {
    _meanAnomaly = offset + ((id % 66) * (2.0 * M_PI) / 66.0);
}

double Satellite::getAnomaly(simtime_picosec currentTime) const {
    simtime_picosec orbitPeriod = timeFromSec(ORBIT_PERIOD_SEC);
    
    double anomalyRot = ((long double)currentTime / (long double) orbitPeriod) * 2 * M_PI;
    return _meanAnomaly + anomalyRot;
}

Eigen::Vector3d Satellite::getPosition(simtime_picosec currentTime) const {
    Eigen::Vector3d startPosition(EARTH_RADIUS + _altitude, 0.0, 0.0);

    Eigen::Vector3d result;
    double anomaly = getAnomaly(currentTime);
    Eigen::AngleAxis<double> m2(anomaly, Eigen::Vector3d(0.0, 0.0, 1.0));
    Eigen::AngleAxis<double> m3( M_PI/2 - _planeInclination, Eigen::Vector3d(1.0, 0.0, 0.0));
    Eigen::AngleAxis<double> m4(_raan, Eigen::Vector3d(0.0, 1.0, 0.0));
    result = m4*m3*m2*startPosition;
    return result;
}