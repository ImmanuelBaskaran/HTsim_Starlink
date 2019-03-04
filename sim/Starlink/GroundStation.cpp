//
//

#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#define EARTH_RADIUS 6371000.0
#define ANGLE_IN_RANGE 0.92
#include <math.h>
#include <cmath>

// I supposed satellite coordinates as a Vector3 and ground station coordinates
// as lat,long, earth radius

float dot(Eigen::Vector3d a, Eigen::Vector3d b)  //calculates dot product of a and b
{
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
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

std::vector<Eigen::Vector3d> GroundStation::getSatellitesInRange(Eigen::Vector3d positionMatrix[24][66], double alt)
{
    std::vector<Eigen::Vector3d> satellitesPos;
    for(int i=0;i<24;i++)
        for(int j=0;j<66;j++){
            Eigen::Vector3d pos= positionMatrix[i][j];
                if(isSatelliteInRange(pos, alt)) {
                    satellitesPos.push_back(pos);
        }
    }
    return satellitesPos;
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon) : CbrSrc(eventlist1,speedFromPktps(166)),
_lat(lat), _lon(lon){

}

