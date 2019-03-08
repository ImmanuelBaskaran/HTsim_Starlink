#pragma once
#include "Satellite.h"
#include <Eigen/Geometry>

#define SATS_PER_PLANE 66

// using namespace Eigen;

class OrbitalPlane {
    private:
        int _id;
        Satellite* _satellites[SATS_PER_PLANE];
        double _raan;
        double _firstSatOffset;
        double _inclination;
        double _satAltitude;
        int satIdToIndex(int satId) const;
    public:
        OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset);
        OrbitalPlane() {}
        Satellite* getSatByID(int satId) const;
        // Eigen::Vector3d const getPosForSat(int satId, simtime_picosec currentTime);
};

