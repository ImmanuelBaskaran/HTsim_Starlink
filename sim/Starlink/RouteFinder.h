

#ifndef SIM_ROUTEFINDER_H
#define SIM_ROUTEFINDER_H


#include <eventlist.h>
#include "ConnectionMatrix.h"
#include "GroundStation.h"

class RouteFinder : public EventSource {

    public:
        RouteFinder(EventList& eventlist, const string& name, ConnectionMatrix* matrix) ;
        virtual void doNextEvent() = 0;
        bool* dijkstra (uint8_t ** connectionMatrix, GroundStation src);
        double getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2);
        inline EventList& eventlist() const {return _eventlist;}
        double** get_dist_sat_conn_matrix(uint8_t** matrix,GroundStation station);
    private:
        ConnectionMatrix* _matrix;
};


#endif //SIM_ROUTEFINDER_H
