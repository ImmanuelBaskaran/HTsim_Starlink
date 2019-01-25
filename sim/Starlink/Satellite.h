#pragma once
#include "ISL.h"
#include <Eigen/Dense>

#define ORBIT_PERIOD_SEC 5739

class Satellite {
    private:
        int _id;
        double _meanAnomaly;
        Vector3 _position;
    public:
        inline Vector3 getPosition() { return _position; };
        void setPosition(const Vector3);
        double getAnomaly(simtime_picosec);
};