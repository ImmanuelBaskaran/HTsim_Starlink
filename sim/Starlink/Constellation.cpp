#include "Constellation.h"
#include "Satellite.h"
#include "OrbitalPlane.h"
#include "StarlinkLib.h"

#define DEBUG_LOOP 0

Constellation::Constellation(EventList& eventlist, const string& name,linkspeed_bps bitrate, mem_b maxsize,
                             QueueLogger* logger): EventSource(eventlist,name) {
    for (int i = 0; i < NUM_ORBITAL_PLANES; i++) {
        _planes[i] = new OrbitalPlane(i + 1, i * toRadian(15), toRadian(53.0), 550000,
                                      i * toRadian(195.0/66.0), bitrate, maxsize, eventlist, logger);
    }

    _connectionMatrix = new ConnectionMatrix();
    _routeFinder = new RouteFinder(*this, *_connectionMatrix);

    // London
    _groundStations[0] = new GroundStation(_eventlist, 51.5074, 0.1278, NUM_SATELLITES + 1, _routeFinder);
    // New York City
    _groundStations[1] = new GroundStation(_eventlist, 40.7128, 74.0060, NUM_SATELLITES + 2, _routeFinder);

    for(int i = 1; i <= NUM_SATELLITES; i++) {
        // Create links between all connected satellites
        for(int j = 1; j <= NUM_SATELLITES; j++){
            Satellite* satI = getSatByID(i);
            Satellite* satJ = getSatByID(j);
            if(_connectionMatrix->areSatellitesConnected(*satI, *satJ)){
                _laserLinks.push_back(make_pair( make_pair(i, j),
                                                 new LaserLink(0, eventlist, *satI, *satJ, true)));
            }
        }
        // Create links between all satellites and all ground stations
        for (int j = NUM_SATELLITES + 1; j < DIST_MATRIX_SIZE; j++) {
            Satellite* sat = getSatByID(i);
            GroundStation* gst = getGroundStation(j);
            _laserLinks.push_back(make_pair( make_pair(i, j),
                                                 new LaserLink(0, eventlist, *sat, *gst, false)));
        }
    }

    #if DEBUG_LOOP
    for(int i = 1; i <= 66; i++){
        int currSat = i;
        int nextSat;
        Eigen::Vector3d pos = getSatByID(currSat)->getPosition(0);
        printf("%f %f %f\n" , pos.x(), pos.y(), pos.z());
        //    printf("%d %f %f %f\n",currSat , pos.x(), pos.y(), pos.z());
        for(int j = 1; j<1585; j++){
            if(_connectionMatrix->areSatellitesConnected(*getSatByID(currSat),*getSatByID(j))){
                // printf("%d connects to %d\n", currSat, j);
                nextSat = j;
                break;
            }
        }
        do{
            int currsatTemp = currSat;
            currSat=nextSat;
            for(int j = 1; j<1585; j++){
                if(_connectionMatrix->areSatellitesConnected(*getSatByID(currSat),*getSatByID(j))){
                    // printf("%d connects to %d\n", currSat, j);
                    nextSat = j;
                    break;
                }
            }

            Eigen::Vector3d pos = getSatByID(currSat)->getPosition(0);
            printf("%f %f %f\n", pos.x(), pos.y(), pos.z());
            //    printf("%d %f %f %f\n",currSat , pos.x(), pos.y(), pos.z());
        } while (currSat != i);
        printf("\n\n");
    }
    #endif

}

Satellite* Constellation::getSatByID(int satId) const {
    assert(satId >= 0 && satId <= NUM_SATELLITES);
    return _planes[(satId-1) / NUM_SATS_PER_PLANE]->getSatByID((satId-1)  % NUM_SATS_PER_PLANE);
}

GroundStation* Constellation::getGroundStation(int id) const {
    int index = id - NUM_SATELLITES - 1;
    assert(index >= 0 && index < NUM_GROUNDSTATIONS);
    return _groundStations[index];
}

Node* Constellation::getNodeById(int id) const {
    if (id <= NUM_SATELLITES) {
        return getSatByID(id);
    } else {
        return getGroundStation(id);
    }
}

LaserLink* Constellation::getConnectingLink(const Node& a, const Node& b) const {
    for (auto& row : _laserLinks) {
        auto& column = row.first;
        if ((column.first == a.getId() && column.second == b.getId())
            || (column.first == b.getId() && column.second == a.getId())) {
            return row.second;
        }
    }
    printf("Could not find link between Nodes %d and %d.\n", a.getId(), b.getId());
    assert(false);
}

void Constellation::doNextEvent() {
    // eventlist().sourceIsPendingRel(*this, timeFromMs(10));
}
