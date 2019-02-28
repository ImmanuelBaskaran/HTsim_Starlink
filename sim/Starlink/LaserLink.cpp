#include "LaserLink.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>


LaserLink::LaserLink(simtime_picosec delay1, EventList &eventlist1,Satellite sat1,Satellite sat2)
        : Pipe(delay1, eventlist1), _sat1(sat1), _sat2(sat2) {
    double distance = getDistanceBetweenSatellitePair(_sat1,_sat2);

    Pipe::_delay = timeFromSec(distance/299792458);


}

void LaserLink::doNextEvent() {

    //TODO: Implement delay change based on link length

    double distance = getDistanceBetweenSatellitePair(_sat1,_sat2);

    Pipe::_delay = timeFromSec(distance/299792458);
    //Pipe::_delay -= 1;

   // printf("%i\n",_sat1.getID());

    //Run regular behavior of Pipe
    Pipe::doNextEvent();
}

Eigen::Vector3f LaserLink::getSatellitePosition(Satellite satellite){

    return satellite.getPosition();
}


double LaserLink::getDistanceBetweenSatellitePair(Satellite satellite1,Satellite satellite2){
    Eigen::Vector3f  position1 = satellite1.getPosition();
    Eigen::Vector3f  position2 = satellite2.getPosition();

    double distance = pow(position2.x()-position1.x(),2)+
            pow(position2.y()-position1.y(),2)+
            pow(position2.z()-position1.z(),2);
    return sqrt(distance);
}