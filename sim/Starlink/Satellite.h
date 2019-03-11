#pragma once
#include "config.h"
#include <Eigen/Dense>
#include <queue.h>
#include "Node.h"

class Satellite :public Node {
    private:
        int _id;
        double _meanAnomaly;
        double _planeInclination;
        double _raan;
        double _altitude;
        Eigen::Vector3d _position;
    public:
        Satellite(int id, double offset, double planeInclination, double raan, double altitude,linkspeed_bps bitrate, mem_b maxsize, EventList &eventlist,
                  QueueLogger* logger);
        Eigen::Vector3d getPosition(simtime_picosec currentTime) const;
        double getAnomaly(simtime_picosec) const;
        inline int getId() const { return _id; }
        Queue queue;
};