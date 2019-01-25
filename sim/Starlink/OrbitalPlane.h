#pragma once
#include "Satellite.h"

#define SATS_PER_PLANE 66
#define EARTH_RADIUS 6371000

class OrbitalPlane {
    private:
        int _id;
        Satellite* _satellites[];
        double _raan;
        double _firstSatOffset;
        double _inclination;
        double _satAltitude;
        void initSatellites();
        int satIdToIndex(int satId);
    public:
        OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset);
        Vector3 const getPosForSat(int satId, simtime_picosec currentTime);
};

