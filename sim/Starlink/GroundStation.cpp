#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#include "Constellation.h"
#include "StarlinkLib.h"
#include "route.h"

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon, int id, RouteFinder* routeFinder)
                             : CbrSrc(eventlist1, speedFromPktps(166)), Node(id), _lat(lat), _lon(lon),
                             _routeFinder(routeFinder) {
    // For routing matrices to add up, ground station IDs must start at NUM_SATELLITES + 1
    assert(id > NUM_SATELLITES);
    std::stringstream ss;
    ss << "GroundStation " << id;
    _nodename = ss.str();
}

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(const Satellite& sat, simtime_picosec currentTime) const
{
    Eigen::Vector3d satPos = sat.getPosition(currentTime);
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

void GroundStation::setDestination(GroundStation* dest) {
    _dest = dest;
}

void GroundStation::send_packet() {
    printf("GroundStation %d sending packet\n", getId());
    // Packet* p = CbrPacket::newpkt(_flow, *_route, _crt_id++, _mss);
    // TODO: Only perform below changes every X ms
    
    assert(_dest);
    _route = _routeFinder->dijkstra(*this, *_dest, _eventlist.now());
    
    CbrSrc::send_packet();
}

void GroundStation::receivePacket(Packet& pkt) {
    printf("GroundStation %d received packet with ID %u\n", getId(), pkt.id());
    pkt.freeRoute();
    CbrSink::receivePacket(pkt);
}