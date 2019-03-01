//
//

#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#define EARTH_RADIUS 6371000
#define ANGLE_IN_RANGE 0.76
#include <math.h>
#include <cmath>

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(const Satellite& satellite, simtime_picosec currentTime)
{
    Eigen::Vector3d gsCartCoords;
    gsCartCoords.x()=EARTH_RADIUS*sin(_lat)*cos(_lon);
    gsCartCoords.y()=EARTH_RADIUS*sin(_lat)*sin(_lon);
    gsCartCoords.z()=EARTH_RADIUS*cos(_lat);

    //the angle we are looking for is the angle between the vector difference (satellite, GS) and GS
    Eigen::Vector3d diffVect;
    diffVect = gsCartCoords - satellite.getPosition();

    //acos = arc cosine of x, expressed in radians
    //.norm() = magnitude of vector
    float angle=std::acos(diffVect.dot(gsCartCoords) / diffVect.norm() * gsCartCoords.norm());
    if(angle<ANGLE_IN_RANGE && angle>ANGLE_IN_RANGE)
          return true;
    return false;
}


std::vector<Satellite> GroundStation::getSatellitesInRange(const vector<Satellite>& positionMatrix)
{
    std::vector<Satellite> satellites;
    for(Satellite satellite : positionMatrix)
        if(isSatelliteInRange(satellite,0)) {
            satellites.push_back(satellite);
        }
    return satellites;
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon) : CbrSrc(eventlist1,speedFromPktps(166)),
_lat(lat), _lon(lon){

}

