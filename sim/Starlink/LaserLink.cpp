#include "LaserLink.h"
#include "Satellite.h"
#include "Satellite.h"
#include "Node.h"
#include <eigen3/Eigen/Dense>


LaserLink::LaserLink(simtime_picosec delay1, EventList &eventlist1, const Node node1, const Node node2, bool isSatelliteLink)
                     : Pipe(delay1, eventlist1), _node1(node1), _node2(node2), _isSatelliteLink(isSatelliteLink) {
    
    Eigen::Vector3d node1Pos = _node1.getPosition(eventlist1.now());
    Eigen::Vector3d node2Pos = _node2.getPosition(eventlist1.now());

    double distance = getDistanceBetweenNodes(node1Pos, node2Pos);
    if(checkIsSatellite()){
        Pipe::_delay = timeFromSec(distance / 299792458);
    }else{
        Pipe::_delay = timeFromSec(distance / 3e+8);
    }
}

void LaserLink::doNextEvent() {
    Eigen::Vector3d node1Pos = _node1.getPosition(_eventlist.now());
    Eigen::Vector3d node2Pos = _node2.getPosition(_eventlist.now());

    double distance = getDistanceBetweenNodes(node1Pos, node2Pos);
    if(checkIsSatellite()){
        Pipe::_delay = timeFromSec(distance / 299792458);
    }else{
        Pipe::_delay = timeFromSec(distance / 3e+8);
    }
    
    Pipe::doNextEvent();
}

double LaserLink::getDistanceBetweenNodes(Eigen::Vector3d node1Position, Eigen::Vector3d node2Position) const {
    return (node2Position - node1Position).norm();
}
