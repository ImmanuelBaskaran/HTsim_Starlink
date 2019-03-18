#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#include "Constellation.h"
#include "StarlinkLib.h"
#include "route.h"

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon, int id,
                             simtime_picosec timeBetweenRouteCalcs, RouteFinder* routeFinder)
                             : CbrSrc(eventlist1, speedFromPktps(1)), Node(id), _lat(lat), _lon(lon),
                             _timeBetweenRouteCalcs(timeBetweenRouteCalcs), _routeFinder(routeFinder) {
    // For routing matrices to add up, ground station IDs must start at NUM_SATELLITES + 1
    assert(id > NUM_SATELLITES);
    _lastRouteCalcTime = 0;
    std::stringstream ss;
    ss << "GroundStation " << id;
    _nodename = ss.str();
}

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(const Satellite& sat, simtime_picosec currentTime) const
{
    Eigen::Vector3d satPos = sat.getPosition(currentTime);
    Eigen::Vector3d gsCartCoords = getPosition(currentTime);

    double distance = (gsCartCoords - satPos).norm();
    double distance_max = ALTITUDE/cos(ANGLE_IN_RANGE);
    if(distance<distance_max)
        return true;
    return false;
}

Eigen::Vector3d GroundStation::getPosition(simtime_picosec currentTime) const {
    Eigen::Vector3d startPosition(EARTH_RADIUS, 0.0, 0.0);
    double rotationDegrees = (currentTime/(8.64e+16)) * 360.0;

    Eigen::AngleAxis<double> m1(-1 * toRadian(_lon), Eigen::Vector3d(0.0,0.0,1.0));
    Eigen::AngleAxis<double> m2(-1 * toRadian(_lat), Eigen::Vector3d(0.0,1.0,0.0));
    Eigen::AngleAxis<double> m3(toRadian(rotationDegrees), Eigen::Vector3d(0.0,0.0,1.0));

    return m3 * m1 * m2 * startPosition;
}

void GroundStation::setDestination(GroundStation* dest) {
    _dest = dest;
    _lastRouteCalcTime = 0;
}

void GroundStation::send_packet() {
    //printf("GroundStation %d sending packet\n", getId());
    if (_lastRouteCalcTime == 0 || _eventlist.now() - _lastRouteCalcTime > _timeBetweenRouteCalcs) {
        _lastRouteCalcTime = _eventlist.now();

        // Mark that ground station is no longer using old route
        if (_route) {
            _route->decrementRefCount();
        }
        assert(_dest);
        // printf("Running Dijkstra...\n");
        _route = _routeFinder->dijkstra(*this, *_dest, _eventlist.now());
        // Mark that ground station is using new route
        _route->incrementRefCount();
    }
    // Mark that packet is using route
    _route->incrementRefCount();
    CbrSrc::send_packet();
}

void GroundStation::receivePacket(Packet& pkt) {
    simtime_picosec delay = _eventlist.now() - pkt.sendTime;
    // // EXPERIMENT DEBUG: Print end-to-end delay of packet
    // printf("%lu %lu\n", _eventlist.now(), delay);
    // EXPERIMENT DEBUG: Print arrival time against packet ID
    // printf("%lu %u\n", _eventlist.now(), pkt.id());

    // Mark that packet is no longer using route
    pkt.route()->decrementRefCount();
    if (pkt.route()->isFree()) {
        // If no one is using route anymore, free it
        // printf("Deleting old route...\n");
        delete pkt.route();
    }
    CbrSink::receivePacket(pkt);
}