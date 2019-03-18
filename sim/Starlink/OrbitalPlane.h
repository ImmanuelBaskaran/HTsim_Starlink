#pragma once
#include "Satellite.h"
#include <Eigen/Geometry>
#include "StarlinkLib.h"

class OrbitalPlane {
    private:
        int _id;
        Satellite* _satellites[NUM_SATS_PER_PLANE];
        double _raan;
        double _inclination;
        double _satAltitude;
        double _firstSatOffset;
    public:
        OrbitalPlane(int id, double raan, double inclination, double satAltitude, double firstSatOffset,
                     linkspeed_bps bitrate, mem_b maxsize, EventList &eventlist, QueueLogger* logger);
        // OrbitalPlane() {}
        Satellite* getSatByID(int zeroedId) const;
        void print_plane(simtime_picosec time);
};

