//
//

#include "GroundStation.h"
#include "Satellite.h"
#include <Eigen/Dense>
#define EARTH_RADIUS 6371000
#define ANGLE_IN_RANGE 0.76
#include <math.h>
#include <vector>
#include <cmath>


// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(Satellite satellite)
{
    Vector3 gsCartCoords;
    gsCartCoords.x()=EARTH_RADIUS*sin(lat)*cos(lon);
    gsCartCoords.y()=EARTH_RADIUS*sin(lat)*sin(lon);
    gsCartCoords.z()=EARTH_RADIUS*cos(lat);

    //the angle we are looking for is the angle between the vector difference (satellite, GS) and GS
    Eigen::Vector3 diffVect;
    diffVect.x()=gsCartCoords.x()-satellite.x();
    diffVect.y()=gsCartCoords.y()-satellite.y();
    diffVect.z()=gsCartCoords.z()-satellite.z();

    //acos = arc cosine of x, expressed in radians
    //mag = magnitude of vector
    float angle=std::acos(dot(diffVect, gsCartCoords)/mag(diffVect)*mag(gsCartCoords));
    if(angle<ANGLE_IN_RANGE &&angle>ANGLE_IN_RANGE)
          return true;
    return false;
}


std::vector<Satellite> GroundStation::getSatellitesInRange(Eigen::Vector3d[][] positionMatrix)
{
    vector<Satellite> satellites=nullptr;
    for(Satellite satellite : positionMatrix)
        if(isSatelliteInRange(satellite.getPosition())
            vector.push_back(satellite);
    return satellites;
}
