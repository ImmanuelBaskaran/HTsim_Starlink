#pragma once
#include "config.h"
#include <Eigen/Dense>
#include <queue.h>
#include "Node.h"

class Satellite : public Node {
    private:
        double _meanAnomaly;
        double _planeInclination;
        double _raan;
        double _altitude;
        Eigen::Vector3d _position;
        Queue* _queue = NULL;
        double getAnomaly(simtime_picosec) const;
    public:
        Satellite(int id, double offset, double planeInclination, double raan, double altitude,
                  linkspeed_bps bitrate, mem_b maxsize, EventList &eventlist, QueueLogger* logger);
        ~Satellite();
        Eigen::Vector3d getPosition(simtime_picosec currentTime) const override;
        inline PacketSink* getPacketSink() override { return _queue; }
};