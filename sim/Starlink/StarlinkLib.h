#pragma once

#define EARTH_RADIUS 6371000.0
#define ANGLE_IN_RANGE 0.92
#define ALTITUDE 550000
#define NUM_ORBITAL_PLANES 24
#define NUM_SATS_PER_PLANE 66
#define ORBIT_PERIOD_SEC 5739
#define NUM_SATELLITES 1584
#define NUM_GROUNDSTATIONS 2
#define DIST_MATRIX_SIZE NUM_SATELLITES + NUM_GROUNDSTATIONS + 1

#define DEBUG_PRINT_E2E_DELAY 1
#define DEBUG_PRINT_SENT_IDS 0
#define DEBUG_PRINT_ARRIVAL_IDS 0
#define DEBUG_PRINT_ROUTE 0
#define DEBUG_PACKETS_PER_SEC 1
#define DEBUG_SIMULATION_START_TIME_IN_PICOSECS 0
#define DEBUG_SIMULATION_END_TIME_IN_SECS 120

#include <math.h>
#include "Node.h"

inline double toRadian(double degrees){
    return (degrees * (M_PI/180));
}

inline double getNodeDistance(const Node& a, const Node& b, simtime_picosec time) {
    return (b.getPosition(time) - a.getPosition(time)).norm();
}