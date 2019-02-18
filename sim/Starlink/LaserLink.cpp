
#include "LaserLink.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>


LaserLink::LaserLink(simtime_picosec delay1, EventList &eventlist1, simtime_picosec delay, EventList &eventlist)
        : Pipe(delay1, eventlist1) {


}

void LaserLink::doNextEvent() {

    //TODO: Implement delay change based on link length


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

