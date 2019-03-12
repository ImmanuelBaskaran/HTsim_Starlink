#pragma once

#include "GroundStation.h"
#include "Satellite.h"
#include "OrbitalPlane.h"
#include "StarlinkLib.h"
#include "ConnectionMatrix.h"
#include "RouteFinder.h"
#include "LaserLink.h"

class Constellation : public EventSource {
    public:
        Constellation(EventList& eventlist, const string& name,linkspeed_bps bitrate, mem_b maxsize,
                      QueueLogger* logger);
        void doNextEvent();
        Satellite* getSatByID(int satId) const;
        GroundStation* getGroundStation(int id) const;
        Node* getNodeById(int id) const;
        LaserLink* getConnectingLink(const Node& a, const Node& b) const;
    private:
        OrbitalPlane* _planes[NUM_ORBITAL_PLANES];
        GroundStation* _groundStations[NUM_GROUNDSTATIONS];
        ConnectionMatrix* _connectionMatrix;
        RouteFinder* _routeFinder;
        vector<pair<pair<int,int>,LaserLink*>> _laserLinks;
};