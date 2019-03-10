#ifndef SIM_ROUTEFINDER_H
#define SIM_ROUTEFINDER_H

#include <eventlist.h>
#include "ConnectionMatrix.h"
#include "Constellation.h"

class RouteFinder : public EventSource {

    public:
        RouteFinder(EventList& eventlist, const string& name, const Constellation& constellation,
                    const ConnectionMatrix& connMatrix);
        virtual void doNextEvent() = 0;
        std::vector<int> dijkstra (const GroundStation& src, const GroundStation& dest);
        double getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2);
        inline EventList& eventlist() const {return _eventlist;}
    private:
        const Constellation& _constellation;
        const ConnectionMatrix& _connMatrix;
        double _distMatrix[DIST_MATRIX_SIZE][DIST_MATRIX_SIZE];

        void updateDistMatrix();
        std::vector<int> extractPath(int* parent, int destId);
        int minDistance(double dist[], bool sptSet[]);
};


#endif //SIM_ROUTEFINDER_H
