#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#include <Eigen/Geometry>
#define EARTH_RADIUS 6371000
#define ANGLE_IN_RANGE 0.76
#include <math.h>
#include <cmath>

using namespace Eigen;

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius
bool GroundStation::isSatelliteInRange(const Satellite& satellite, simtime_picosec currentTime) 
{
   Vector3d startPosition(EARTH_RADIUS, 0.0, 0.0);
    // gsCartCoords.x()=EARTH_RADIUS*sin(_lat)*cos(_lon);
    // gsCartCoords.y()=EARTH_RADIUS*sin(_lat)*sin(_lon);
    // gsCartCoords.z()=EARTH_RADIUS*cos(_lat);

    Vector3d gsCartCoords;

    double rotationDegrees = (currentTime/(8.64e+16)) * 360;

    AngleAxis<double> m1(_lon, Vector3d(0.0,0.0,1.0));
    AngleAxis<double> m2(_lat, Vector3d(0.0,1.0,0.0));
    AngleAxis<double> m3(rotationDegrees, Vector3d(0.0,0.0,1.0));

    gsCartCoords = m3 * m2 * m1 * startPosition;



    //the angle we are looking for is the angle between the vector difference (satellite, GS) and GS
    Vector3d diffVect;
    diffVect = gsCartCoords - satellite.getPosition();

    //acos = arc cosine of x, expressed in radians
    //.norm() = magnitude of vector
    float angle=std::acos(diffVect.dot(gsCartCoords) / diffVect.norm() * gsCartCoords.norm());
    if(angle<ANGLE_IN_RANGE && angle>ANGLE_IN_RANGE)
          return true;
    return false;
}


std::vector<Satellite> GroundStation::getSatellitesInRange(const vector<Satellite>& positionMatrix, simtime_picosec currentTime)
{
    std::vector<Satellite> satellites;
    for(Satellite satellite : positionMatrix)
        if(isSatelliteInRange(satellite,currentTime)) {
            satellites.push_back(satellite);
        }
    return satellites;
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon) : CbrSrc(eventlist1,speedFromPktps(166)),
_lat(lat), _lon(lon){

}

