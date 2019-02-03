#include "Satellite.h"
#include <math.h>

Satellite::Satellite(int id, double offset) : _id(id) {
    _meanAnomaly = ((id % 66) * (2 * M_PI / 66.0) + offset) % 2 * M_PI;
}


double Satellite::getAnomaly(simtime_picosec currentTime) {
    simtime_picosec orbitPeriod = timeFromSec(ORBIT_PERIOD_SEC);
    
    double anomalyRot = (currentTime / orbitPeriod) * 2 * M_PI;
    return _meanAnomaly + anomalyRot;
}