#pragma once
#include "config.h"
#include <eigen3/Eigen/Dense>

#define ORBIT_PERIOD_SEC 5739



class Satellite {
    private:
        int _id;
        double _meanAnomaly;
        Eigen::Vector3d _position;
    public:
        Satellite(int id, double offset);
        inline Eigen::Vector3d getPosition() const { return _position; };
        inline int getID() { return _id; };
        inline void setPosition(const Eigen::Vector3d position) {_position = position;};
        double getAnomaly(simtime_picosec);
};