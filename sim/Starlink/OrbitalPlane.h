#pragma once
#include "Satellite.h"
#include <Eigen/Geometry>

#define SATS_PER_PLANE 66
#define EARTH_RADIUS 6371000

class OrbitalPlane {
    private:
        int _id;
        Satellite* _satellites[SATS_PER_PLANE];
        double _planeOffset;
        double _raan;
        double _firstSatOffset;
        double _inclination;
        double _satAltitude;
        int satIdToIndex(int satId);
    public:
        OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset);
        Vector3d const getPosForSat(int satId, simtime_picosec currentTime);
};

