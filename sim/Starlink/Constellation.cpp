#include "Constellation.h"
#include "Satellite.h"
#include "OrbitalPlane.h"
#include "StarlinkLib.h"


Constellation::Constellation(EventList& eventlist, const string& name,linkspeed_bps bitrate, mem_b maxsize,
                             QueueLogger* logger): EventSource(eventlist,name) {
    for (int i = 0; i < NUM_ORBITAL_PLANES; i++) {
        _planes[i] = new OrbitalPlane(i + 1, i * toRadian(15), toRadian(53.0), 550000, i * toRadian(195.0/66.0),
                                      bitrate, maxsize, eventlist,
                logger);
        for (int j = 0; j < SATS_PER_PLANE; j++) {
            Eigen::Vector3d pos = _planes[i]->getSatByID(j)->getPosition(0);
            // printf("Plane %d, Sat %d: %f %f %f\n", i, j, pos.x(), pos.y(), pos.z());
        }
    }

    _connectionMatrix = new ConnectionMatrix();
    _routeFinder = new RouteFinder(*this, *_connectionMatrix);

    // London
    _groundStations[0] = new GroundStation(_eventlist, 51.5074, 0.1278, NUM_SATELLITES + 1, _routeFinder);
    // New York City
    _groundStations[1] = new GroundStation(_eventlist, 40.7128, 74.0060, NUM_SATELLITES + 2, _routeFinder);

    for(int i = 1; i <= NUM_SATELLITES; i++){
        for(int j = 1; j <= NUM_SATELLITES; j++){
            Satellite* satI = getSatByID(i);
            Satellite* satJ = getSatByID(j);
            if(_connectionMatrix->areSatellitesConnected(*satI, *satJ)){
                _laserLinks.push_back(make_pair( make_pair(i, j),
                                                 new LaserLink(0, eventlist,*getSatByID(i-1), *getSatByID(j-1))));
            }
        }
    }
}

Satellite* Constellation::getSatByID(int satId) const {
    assert(satId > 0 && satId <= NUM_SATELLITES);
    return _planes[satId / SATS_PER_PLANE]->getSatByID(satId % SATS_PER_PLANE);
}

GroundStation* Constellation::getGroundStation(int id) const {
    int index = id - NUM_SATELLITES - 1;
    assert(index >= 0 && index < NUM_GROUNDSTATIONS);
    return _groundStations[index];
}

LaserLink* Constellation::getConnectingLink(const Satellite& satA, const Satellite& satB) const {
    for (auto& row : _laserLinks) {
        auto& column = row.first;
        if (column.first == satA.getID() && column.second == satB.getID()) {
            return row.second;
        }
    }
    printf("Could not find link between Sat. %d and Sat. %d.\n", satA.getID(), satB.getID());
    assert(false);
}



void Constellation::doNextEvent() {
    // eventlist().sourceIsPendingRel(*this, timeFromMs(10));
}
