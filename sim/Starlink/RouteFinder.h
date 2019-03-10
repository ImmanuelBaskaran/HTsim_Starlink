#ifndef SIM_ROUTEFINDER_H
#define SIM_ROUTEFINDER_H

#include <eventlist.h>
#include "ConnectionMatrix.h"
#include "Constellation.h"

class RouteFinder : public EventSource {

    public:
        RouteFinder(EventList& eventlist, const string& name, const Constellation& constellation);
        virtual void doNextEvent() = 0;
        std::vector<int> dijkstra (uint8_t ** connectionMatrix, const GroundStation& src,
                          const GroundStation& dest);
        double getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2);
        inline EventList& eventlist() const {return _eventlist;}
    private:
        const Constellation& _constellation;
        double _distMatrix[DIST_MATRIX_SIZE][DIST_MATRIX_SIZE];

        void updateDistMatrix(uint8_t** matrix);
        std::vector<int> extractPath(int* parent, int destId);
        int minDistance(double dist[], bool sptSet[]);
};


#endif //SIM_ROUTEFINDER_H
