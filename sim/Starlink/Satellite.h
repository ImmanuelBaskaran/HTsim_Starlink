#pragma once
#include "config.h"
#include <Eigen/Dense>
#include <queue.h>

#define ORBIT_PERIOD_SEC 5739
#define EARTH_RADIUS 6371000

class Satellite {
    private:
        int _id;
        double _meanAnomaly;
        double _planeInclination;
        double _raan;
        double _altitude;
        Eigen::Vector3d _position;
    public:
        Satellite(int id, double offset, double planeInclination, double raan, double altitude);
        Eigen::Vector3d getPosition(simtime_picosec currentTime) const;
        inline int getID() const { return _id; };
        double getAnomaly(simtime_picosec) const;
};