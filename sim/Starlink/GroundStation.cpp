//
//

#include "GroundStation.h"
#include "Satellite.h"
#include <eigen3/Eigen/Dense>
#define EARTH_RADIUS 6371000.0
#define ANGLE_IN_RANGE 0.92
#define ALTITUDE 550000
#define NUM_SATELLITES 1584
#include <math.h>
#include <cmath>
#include <sstream>
#include <string.h>
#include <strstream>
#include <iostream>
#include "Constellation.h"

double toRadian(double degrees){
    return (degrees * (M_PI/180));
}

// I supposed satellite coordinates as a Vector3 and ground station coordinates

bool GroundStation::isSatelliteInRange(const Satellite& sat)
{
    Eigen::Vector3d gsCartCoords;
    Eigen::Vector3d satPos = sat.getPosition(_eventlist.now());
    gsCartCoords.x()=EARTH_RADIUS*sin(_lat)*cos(_lon);
    gsCartCoords.y()=EARTH_RADIUS*sin(_lat)*sin(_lon);
    gsCartCoords.z()=EARTH_RADIUS*cos(_lat);

    double distance = sqrt(pow((gsCartCoords.x()-satPos.x()),2)+pow((gsCartCoords.y()-satPos.y()),2)+pow((gsCartCoords.z()-satPos.z()),2));

    double distance_max = ALTITUDE/cos(ANGLE_IN_RANGE);
    if(distance<distance_max)
        return true;
    return false;

}

std::vector<Satellite*> GroundStation::getSatellitesInRange(const Constellation& constellation)
{
    _satsInRange.clear();
    for (int i = 1; i <= NUM_SATELLITES; i++) {
        Satellite* sat = constellation.getSatByID(i);
        if (isSatelliteInRange(*sat)) {
            _satsInRange.push_back(sat);
        }
    }
    return _satsInRange;
}

GroundStation::GroundStation(EventList &eventlist1,double lat, double lon, int id) : CbrSrc(eventlist1,speedFromPktps(166)),
_lat(lat), _lon(lon), _id(id){

}