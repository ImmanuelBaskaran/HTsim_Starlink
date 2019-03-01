#pragma once
#include "config.h"
#include <Eigen/Dense>
#include <queue.h>

#define ORBIT_PERIOD_SEC 5739

class Satellite {
    private:
        int _id;
        double _meanAnomaly = 0;
        Eigen::Vector3d _position;
    public:
        Satellite(int id, double offset);
        inline Eigen::Vector3d getPosition() const { return _position; };
        inline int getID() const { return _id; };
        inline void setPosition(Eigen::Vector3d position) {_position = position;};
        double getAnomaly(simtime_picosec) const;
};