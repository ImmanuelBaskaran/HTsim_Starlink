//
//

#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#define EARTH_RADIUS 6371000.0
#define ANGLE_IN_RANGE 0.92
#define ALTITUDE 550000
#include <math.h>
#include <cmath>
#include <sstream>
#include <string.h>
#include <strstream>
#include <iostream>
#include "OrbitalPlane.h"

double toRadian(double degrees){
    return (degrees * (M_PI/180));
}

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(const Satellite& satellite)
{
    Eigen::Vector3d gsCartCoords;
    gsCartCoords.x()=EARTH_RADIUS*sin(_lat)*cos(_lon);
    gsCartCoords.y()=EARTH_RADIUS*sin(_lat)*sin(_lon);
    gsCartCoords.z()=EARTH_RADIUS*cos(_lat);

    //the angle we are looking for is the angle between the vector difference (satellite, GS) and GS
    Eigen::Vector3d diffVect;
    diffVect = gsCartCoords - satellite.getPosition(_eventlist.now());

    //acos = arc cosine of x, expressed in radians
    //.norm() = magnitude of vector
    float angle=std::acos(diffVect.dot(gsCartCoords) / diffVect.norm() * gsCartCoords.norm());
    if(angle<ANGLE_IN_RANGE && angle>ANGLE_IN_RANGE)
          return true;
    return false;

}

std::vector<Eigen::Vector3d> GroundStation::getSatellitesInRange(Eigen::Vector3d positionMatrix[24][66], double alt)
{
    std::vector<Eigen::Vector3d> satellitesPos;

    int id = 1;
    for (int i = 0; i < 24; i++) {
        OrbitalPlane plane(i + 1, toRadian(i * 15.0), toRadian(53.0), ALTITUDE, toRadian(i * 5.5));
        for (int j = 0; j < 66; j++) {
            Satellite* sat = plane.getSatByID(id++);
            if (isSatelliteInRange(*sat))
                satellitesPos.push_back(sat->getPosition(_eventlist.now()));
        }
    }
    return satellitesPos;
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon) : CbrSrc(eventlist1,speedFromPktps(166)),
_lat(lat), _lon(lon){

}

