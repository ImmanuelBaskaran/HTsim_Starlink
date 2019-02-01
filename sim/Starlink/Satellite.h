#pragma once
#include "ISL.h"
#include <Eigen/Dense>

using namespace Eigen;

#define ORBIT_PERIOD_SEC 5739

class Satellite {
    private:
        int _id;
        double _meanAnomaly;
        Vector3f _position;
    public:
        Satellite(const int id, const double offset);
        inline Vector3f getPosition() { return _position; };
        void setPosition(const Vector3f);
        double getAnomaly(simtime_picosec);
};