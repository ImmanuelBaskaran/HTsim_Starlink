#include "Satellite.h"
#include <math.h>

Satellite::Satellite(const int id, const double offset) : _id(id) {
    _meanAnomaly = offset + ((id % 66) * (2.0 * M_PI) / 66.0);
}

double Satellite::getAnomaly(simtime_picosec currentTime) {
    simtime_picosec orbitPeriod = timeFromSec(ORBIT_PERIOD_SEC);
    
    double anomalyRot = (currentTime / orbitPeriod) * 2 * M_PI;
    return _meanAnomaly + anomalyRot;
}