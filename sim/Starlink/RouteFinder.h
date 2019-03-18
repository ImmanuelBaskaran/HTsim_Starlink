#ifndef SIM_ROUTEFINDER_H
#define SIM_ROUTEFINDER_H

#include <eventlist.h>
#include "StarlinkLib.h"
#include "ConnectionMatrix.h"

// Avoid circular dependencies
class Constellation;
class GroundStation;

class RouteFinder {
    public:
        RouteFinder(const Constellation& constellation, const ConnectionMatrix& connMatrix);
        route_t* dijkstra (const GroundStation& src, const GroundStation& dest, simtime_picosec now);
    private:
        const Constellation& _constellation;
        const ConnectionMatrix& _connMatrix;
        double _distMatrix[DIST_MATRIX_SIZE][DIST_MATRIX_SIZE];

        void updateDistMatrix(simtime_picosec now);
        std::vector<int> extractPath(int* parent, int destId);
        int minDistance(double dist[], bool sptSet[]);
        void printPath(std::vector<int> path, simtime_picosec now);
};


#endif //SIM_ROUTEFINDER_H
