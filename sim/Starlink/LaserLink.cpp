#include "LaserLink.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>


LaserLink::LaserLink(simtime_picosec delay1, EventList &eventlist1, const Satellite& sat1, const Satellite& sat2)
        : Pipe(delay1, eventlist1), _sat1(sat1), _sat2(sat2) {
    double distance = getDistanceBetweenSatellitePair(_sat1,_sat2);

    Pipe::_delay = timeFromSec(distance/299792458);
}

void LaserLink::doNextEvent() {

    //TODO: Implement delay change based on link length

    double distance = getDistanceBetweenSatellitePair(_sat1,_sat2);

    Pipe::_delay = timeFromSec(distance / 299792458);
    //Pipe::_delay -= 1;

    //Run regular behavior of Pipe
    Pipe::doNextEvent();
}

Eigen::Vector3f LaserLink::getSatellitePosition(const Satellite& satellite){

    return satellite.getPosition();
}


double LaserLink::getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2){
    Eigen::Vector3d position1 = satellite1.getPosition();
    Eigen::Vector3d position2 = satellite2.getPosition();
    return (position2 - position1).norm();
}