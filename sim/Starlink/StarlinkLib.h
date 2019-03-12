#pragma once

#define EARTH_RADIUS 6371000.0
#define ANGLE_IN_RANGE 0.92
#define ALTITUDE 550000
#define NUM_SATELLITES 1584
#define NUM_ORBITAL_PLANES 24
#define NUM_SATS_PER_PLANE 66
#define ORBIT_PERIOD_SEC 5739
#define NUM_SATELLITES 1584
#define NUM_GROUNDSTATIONS 2
#define DIST_MATRIX_SIZE NUM_SATELLITES + NUM_GROUNDSTATIONS + 1

#include <math.h>
#include "Node.h"

inline double toRadian(double degrees){
    return (degrees * (M_PI/180));
}

inline double getNodeDistance(const Node& a, const Node& b, simtime_picosec time) {
    return (b.getPosition(time) - a.getPosition(time)).norm();
}