#pragma once
#include "config.h"
#include <Eigen/Dense>
#include <queue.h>

#define ORBIT_PERIOD_SEC 5739



class Satellite {
    private:
        int _id;
        double _meanAnomaly = 0;
        Eigen::Vector3f _position;
    public:
        Satellite(int id, double offset);
        inline Eigen::Vector3f getPosition() { return _position; };
        inline int getID() { return _id; };
        inline void setPosition(const Eigen::Vector3f position) {_position = position;};
        double getAnomaly(simtime_picosec);
};