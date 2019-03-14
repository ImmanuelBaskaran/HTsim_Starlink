#include "OrbitalPlane.h"

OrbitalPlane::OrbitalPlane(int id, double raan, double inclination, double satAltitude,
                           double firstSatOffset,linkspeed_bps bitrate, mem_b maxsize,
                           EventList &eventlist, QueueLogger* logger) : _id(id), _raan(raan),
                           _satAltitude(satAltitude), _inclination(inclination),
                           _firstSatOffset(firstSatOffset) {
    for (int i = 0; i < NUM_SATS_PER_PLANE; i++) {
        int satId = (NUM_SATS_PER_PLANE * (_id - 1)) + i + 1;
        _satellites[i] = new Satellite(satId, _firstSatOffset, inclination, raan, satAltitude,bitrate,maxsize,eventlist,logger);
    }
}

Satellite* OrbitalPlane::getSatByID(int zeroedId) const {
    return _satellites[zeroedId % 66];
}
