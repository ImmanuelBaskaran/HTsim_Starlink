#pragma once
#include "Satellite.h"
#include "eigen3/Eigen/Dense"

#define SATS_PER_PLANE 66
#define EARTH_RADIUS 6371000

class OrbitalPlane {
    private:
        int _id;
        double _raan;
        double _firstSatOffset;
        double _inclination;
        double _satAltitude;
        void initSatellites();
        int satIdToIndex(int satId);
        Satellite* _satellites[];
    public:
        OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset);
        const Eigen::Vector3d getPosForSat(int satId, simtime_picosec currentTime);
};

