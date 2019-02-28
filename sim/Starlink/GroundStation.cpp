//
//

#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#define EARTH_RADIUS 6371000
#define ANGLE_IN_RANGE 0.76
#include <math.h>
#include <cmath>

float dot(Eigen::Vector3f a,Eigen::Vector3f b){
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

float mag(Eigen::Vector3f a){
    return std::sqrt(a.x() * a.x() + a.y() * a.y() + a.z() * a.z());
}

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(Satellite satellite)
{
    Eigen::Vector3f gsCartCoords;
    gsCartCoords.x()=EARTH_RADIUS*sin(lat)*cos(lon);
    gsCartCoords.y()=EARTH_RADIUS*sin(lat)*sin(lon);
    gsCartCoords.z()=EARTH_RADIUS*cos(lat);

    //the angle we are looking for is the angle between the vector difference (satellite, GS) and GS
    Eigen::Vector3f diffVect;
    diffVect.x()=gsCartCoords.x()-satellite.getPosition().x();
    diffVect.y()=gsCartCoords.y()-satellite.getPosition().y();
    diffVect.z()=gsCartCoords.z()-satellite.getPosition().z();

    //acos = arc cosine of x, expressed in radians
    //mag = magnitude of vector
    float angle=std::acos(dot(diffVect, gsCartCoords)/mag(diffVect)*mag(gsCartCoords));
    if(angle<ANGLE_IN_RANGE && angle>ANGLE_IN_RANGE)
          return true;
    return false;
}


std::vector<Satellite> GroundStation::getSatellitesInRange(vector<Satellite> positionMatrix)
{
    std::vector<Satellite> satellites;
    for(Satellite satellite : positionMatrix)
        if(isSatelliteInRange(satellite)) {
            satellites.push_back(satellite);
        }
    return satellites;
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon) : CbrSrc(eventlist1,speedFromPktps(1),0.8,1000),
lat(lat),lon(lon){

}

