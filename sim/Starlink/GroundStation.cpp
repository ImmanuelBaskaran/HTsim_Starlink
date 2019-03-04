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



// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius

float dot(Eigen::Vector3d a, Eigen::Vector3d b)  //calculates dot product of a and b
{
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

double GroundStation::toRadians(double degrees){
    return (degrees * (M_PI/180));
}

bool GroundStation::isSatelliteInRange(Eigen::Vector3d satPos, double alt)
{
    Eigen::Vector3d gsCartCoords;
    double flat = 0;
    double ls = atan(pow((1 - flat),2) * tan(_lat));
    //gsCartCoords.x()=EARTH_RADIUS*cos(ls)*cos(_lon) +alt*cos(_lat)*cos(_lon);
    //gsCartCoords.y()=EARTH_RADIUS*cos(ls)*sin(_lon) +alt*cos(_lat)*sin(_lon);
    //gsCartCoords.z()=EARTH_RADIUS*sin(ls)+alt*sin(_lat);
    gsCartCoords.x()=EARTH_RADIUS*sin(_lat)*cos(_lon);
    gsCartCoords.y()=EARTH_RADIUS*sin(_lat)*sin(_lon);
    gsCartCoords.z()=EARTH_RADIUS*cos(_lat);

    double distance = sqrt(pow((gsCartCoords.x()-satPos.x()),2)+pow((gsCartCoords.y()-satPos.y()),2)+pow((gsCartCoords.z()-satPos.z()),2));

    double distance_max = alt/cos(ANGLE_IN_RANGE);
    if(distance<distance_max)
        return true;
    return false;

}

std::vector<Eigen::Vector3d> GroundStation::getSatellitesInRange()
{
    std::vector<Eigen::Vector3d> satellitesPos;

    int id = 1;
    for (int i = 0; i < 24; i++) {
        OrbitalPlane plane(i + 1, toRadians(i * 15.0), toRadians(53.0), ALTITUDE, toRadians(i * 5.5));
        for (int j = 0; j < 66; j++) {
            Eigen::Vector3d pos = plane.getPosForSat(id++, timeFromSec(0));
            if (isSatelliteInRange(pos, ALTITUDE))
                satellitesPos.push_back(pos);
        }
    }
    return satellitesPos;
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon) : CbrSrc(eventlist1,speedFromPktps(166)),
                                                                             _lat(lat), _lon(lon){

}