#include "LaserLink.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>


LaserLink::LaserLink(simtime_picosec delay1, EventList &eventlist1, const Satellite sat1, const Satellite sat2)
        : Pipe(delay1, eventlist1), _sat1(sat1), _sat2(sat2) {
    double distance = getDistanceBetweenSatellitePair(_sat1,_sat2, eventlist1.now());

    Pipe::_delay = timeFromSec(distance/299792458);
}

void LaserLink::doNextEvent() {

    //TODO: Implement delay change based on link length

    double distance = getDistanceBetweenSatellitePair(_sat1,_sat2, _eventlist.now());

    Pipe::_delay = timeFromSec(distance / 299792458);
    //Pipe::_delay -= 1;

    // printf("%i\n",_sat1.getID());


    //Run regular behavior of Pipe
    Pipe::doNextEvent();
}

double LaserLink::getDistanceBetweenSatellitePair(const Satellite& satellite1, 
const Satellite& satellite2, simtime_picosec currentTime) const {
    Eigen::Vector3d position1 = satellite1.getPosition(currentTime);
    Eigen::Vector3d position2 = satellite2.getPosition(currentTime);
    return (position2 - position1).norm();
}