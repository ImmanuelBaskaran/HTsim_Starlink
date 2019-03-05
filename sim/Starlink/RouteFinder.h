

#ifndef SIM_ROUTEFINDER_H
#define SIM_ROUTEFINDER_H


#include <eventlist.h>
#include "ConnectionMatrix.h"

class RouteFinder{
    public:
        RouteFinder(EventList& eventlist, const string& name, uint8_t **matrix);
        //virtual void doNextEvent() = 0;
        void RouteFinder::dijkstra(Satellite src);
        double RouteFinder::getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2);
        //inline EventList& eventlist() const {return _eventlist;}
        double** RouteFinder::get_dist_sat_conn_matrix(uint8_t** matrix);
        double RouteFinder::toRadians(double degrees);
        double** RouteFinder::getDistMatrix();
        int RouteFinder::minDistance(double dist[], bool sptSet[]);
    private:
        uint8_t** _matrix;
        EventList _eventlist;
        double** dist_matrix;
};


#endif //SIM_ROUTEFINDER_H
