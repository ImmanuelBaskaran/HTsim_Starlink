//
// Created by metal on 25/01/19.
//

#include "LaserLink.h"
#include <eigen3/Eigen/Dense>

void LaserLink::doNextEvent() {

    //TODO: Implement delay change based on link length


    //Run regular behavior of Pipe
    Pipe::doNextEvent();
}

Eigen::Vector3d LaserLink::getSatellitePosition(Satellite satellite){

    return satellite.getPosition(EventSource::eventlist().now());
}


double LaserLink::getDistanceBetweenSatellitePair(Satellite satellite1,Satellite satellite2){
    Eigen::Vector3d  position1 = getSatellitePosition(satellite1);
    Eigen::Vector3d  position2 = getSatellitePosition(satellite2);

    double distance = pow(position2.x()-position1.x(),2)+
            pow(position2.y()-position1.y(),2)+
            pow(position2.z()-position1.z(),2);

    return sqrt(distance);
}

