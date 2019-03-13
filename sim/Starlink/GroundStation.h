#pragma once

#include "network.h"
#include "cbr.h"
#include "Satellite.h"
#include "RouteFinder.h"
#include "Node.h"
#include <Eigen/Geometry>

class GroundStation: public CbrSink, public CbrSrc, public Node {
    private:
        double _lat, _lon;
        RouteFinder* _routeFinder;
        GroundStation* _dest = NULL;
    public:
        GroundStation(EventList &eventlist1, double lat, double lon, int id, RouteFinder* routeFinder);
        bool isSatelliteInRange(const Satellite& sat, simtime_picosec currentTime) const;
        Eigen::Vector3d getPosition(simtime_picosec currentTime) const override;
        void setDestination(GroundStation* dest);
        void send_packet() override;
        inline PacketSink* getPacketSink() override { return this; }
};