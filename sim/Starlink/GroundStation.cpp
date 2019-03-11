#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#include "Constellation.h"
#include "StarlinkLib.h"
#include "route.h"

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(const Satellite& sat, simtime_picosec currentTime) const
{
    Eigen::Vector3d satPos = sat.getPosition(_eventlist.now());
    Eigen::Vector3d gsCartCoords;
    gsCartCoords = getPosition(currentTime);

    double distance = (gsCartCoords - satPos).norm();
    double distance_max = ALTITUDE/cos(ANGLE_IN_RANGE);
    if(distance<distance_max)
        return true;
    return false;
}

Eigen::Vector3d GroundStation::getPosition(simtime_picosec currentTime) const {
    Eigen::Vector3d startPosition(EARTH_RADIUS, 0.0, 0.0);
    double rotationDegrees = (currentTime/(8.64e+16)) * 360.0;

    Eigen::AngleAxis<double> m1(_lon, Eigen::Vector3d(0.0,0.0,1.0));
    Eigen::AngleAxis<double> m2(_lat, Eigen::Vector3d(0.0,1.0,0.0));
    Eigen::AngleAxis<double> m3(rotationDegrees, Eigen::Vector3d(0.0,0.0,1.0));

    return m3 * m2 * m1 * startPosition;
}

void GroundStation::send_packet() {
    // Packet* p = CbrPacket::newpkt(_flow, *_route, _crt_id++, _mss);
    // TODO: Only perform below changes every X ms
    delete _route;
    _route = _routeFinder->dijkstra(*this, _dest, _eventlist.now());
    
    
    CbrSrc::send_packet();
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon, int id, RouteFinder* routeFinder)
                             : CbrSrc(eventlist1,speedFromPktps(166)), Node(id), _lat(lat), _lon(lon),
                             _routeFinder(routeFinder) {
    // For routing matrices to add up, ground station IDs must start at NUM_SATELLITES + 1
    assert(id > NUM_SATELLITES);
}