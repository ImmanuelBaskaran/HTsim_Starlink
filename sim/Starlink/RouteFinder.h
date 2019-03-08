

#ifndef SIM_ROUTEFINDER_H
#define SIM_ROUTEFINDER_H


#include <eventlist.h>
#include "ConnectionMatrix.h"
#include "Constellation.h"


#define NUM_SATELLITES 1584
#define NUM_GROUNDSTATIONS 2
#define DIST_MATRIX_SIZE NUM_SATELLITES + NUM_GROUNDSTATIONS

class RouteFinder : public EventSource {

    public:
        RouteFinder(EventList& eventlist, const string& name, ConnectionMatrix* matrix, const Constellation& constellation);
        virtual void doNextEvent() = 0;
        double* dijkstra (uint8_t ** connectionMatrix, const GroundStation& src);
        double getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2);
        inline EventList& eventlist() const {return _eventlist;}
        double** get_dist_sat_conn_matrix(uint8_t** matrix,GroundStation station);
    private:
        ConnectionMatrix* _matrix;
        const Constellation& _constellation;
        double* _dist = NULL;
        void cleanup(double** dist_matrix);
};


#endif //SIM_ROUTEFINDER_H
