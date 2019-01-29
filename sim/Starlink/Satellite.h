#pragma once
#include "ISL.h"
#include <eigen3/Eigen/Dense>

#define ORBIT_PERIOD_SEC 5739



class Satellite {
    private:
        int _id;
        double _meanAnomaly;
        Eigen::Vector3f _position;
    public:
        inline Eigen::Vector3f getPosition() { return _position; };
        void setPosition(const Eigen::Vector3f);
        double getAnomaly(simtime_picosec);
};