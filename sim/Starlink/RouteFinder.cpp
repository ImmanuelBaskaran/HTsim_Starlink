#include "Satellite.h"
#include "RouteFinder.h"
#include "ConnectionMatrix.h"
#include "network.h"
#include "OrbitalPlane.h"
#include "GroundStation.h"
<<<<<<< HEAD
=======

#define NUM_SATELLITES 1584
>>>>>>> 941d77a14eea677ad2ab2afd21311e55605578be

double RouteFinder::getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2){
    Eigen::Vector3d position1 = satellite1.getPosition(_eventlist.now());
    Eigen::Vector3d  position2 = satellite2.getPosition(_eventlist.now());
    return (position2 - position1).norm();
}


double toRadians(double degrees){
    return (degrees * (M_PI/180));
}

//construct distances matrix

double** RouteFinder::get_dist_sat_conn_matrix(uint8_t** matrix) {
    double** dist_matrix = nullptr;
    dist_matrix = new double*[DIST_MATRIX_SIZE];

    for(int i=0;i<NUM_SATELLITES;i++) {
        int iPlaneIndex = i % 24;
        for (int j = 0; j < NUM_SATELLITES; j++) {
            dist_matrix[i] = new double[DIST_MATRIX_SIZE];
            if (matrix[i][j] == 1) {
                Satellite* sat_i = _constellation.getSatByID(i);
                Satellite* sat_j = _constellation.getSatByID(j);
                dist_matrix[i][j] = getDistanceBetweenSatellitePair(*sat_i, *sat_j);
            } else
                dist_matrix[i][j]=INFINITY;
        }
        for (int j = NUM_SATELLITES; j < DIST_MATRIX_SIZE; j++) {
            Satellite* sat = _constellation.getSatByID(i);
            GroundStation* gst = _constellation.getGroundStation(j - NUM_SATELLITES);
            dist_matrix[i][j] = (sat->getPosition(_eventlist.now()) - gst->getPosition()).norm();
        }
    }
    for (int i = NUM_SATELLITES; i < DIST_MATRIX_SIZE; i++) {
        for (int j = 0; j < NUM_SATELLITES; j++) {
            dist_matrix[i] = new double[DIST_MATRIX_SIZE];
            Satellite* sat = _constellation.getSatByID(j);
            GroundStation* gst = _constellation.getGroundStation(i - NUM_SATELLITES);
            dist_matrix[i][j] = (sat->getPosition(_eventlist.now()) - gst->getPosition()).norm();
        }
        for (int j = NUM_SATELLITES; j < DIST_MATRIX_SIZE; j++) {
            dist_matrix[i][j] = INFINITY;
        }
    }

    for(int i=NUM_SATELLITES;i<NUM_SATELLITES+1;i++) {
        for(int j=0;j<NUM_SATELLITES;j++) {
            int jPlaneIndex = j % 24;
            if(source.isSatelliteInRange(planes[jPlaneIndex].getSatByID(j))){
                dist_matrix[i][j]=-300;
            }
        }
    }

    return dist_matrix;
}

int minDistance(double dist[], bool sptSet[]) {
    // Initialize min value
    double min = INFINITY;
    int min_index=INFINITY;

    for (int v = 0; v < DIST_MATRIX_SIZE; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

<<<<<<< HEAD
double* RouteFinder::dijkstra (uint8_t ** connectionMatrix, const GroundStation& src) {
    double** dist_matrix = get_dist_sat_conn_matrix(connectionMatrix);
=======
bool* RouteFinder::dijkstra (uint8_t ** connectionMatrix, GroundStation src)
{
    double** dist_matrix = get_dist_sat_conn_matrix(connectionMatrix,src);
>>>>>>> 941d77a14eea677ad2ab2afd21311e55605578be

    delete[] _dist;

    _dist = new double[DIST_MATRIX_SIZE];   //output, will hold the shortest distance from src to i, should to to sink
    bool sptSet[DIST_MATRIX_SIZE];    //shortest path tree set, keeps track of satellite links included

    for(int i=0;i< DIST_MATRIX_SIZE;i++) {
        _dist[i] = INT_MAX;
        sptSet[i] = false;
    }
<<<<<<< HEAD
    _dist[src.getId()] = 0;
=======
    dist[NUM_SATELLITES] = 0;
>>>>>>> 941d77a14eea677ad2ab2afd21311e55605578be

    for(int count =0; count<DIST_MATRIX_SIZE-1; count++) {
        int u = minDistance(_dist, sptSet); //pick minimum distance link not yet included to sptSet
        sptSet[u] = true;
        for (int v = 0; v < DIST_MATRIX_SIZE; v++) {
            if (!sptSet[v] && dist_matrix[u][v] != 0 && _dist[u] != INT_MAX && _dist[u] + dist_matrix[u][v] < _dist[v]) {
                _dist[v] = _dist[u] + dist_matrix[u][v];
            }
        }
    }
    cleanup(dist_matrix);
    return _dist;
}

void RouteFinder::cleanup(double** dist_matrix) {
    for (int i = 0; i < DIST_MATRIX_SIZE; i++) {
        delete[] dist_matrix[i];
    }
    delete[] dist_matrix;
}


RouteFinder::RouteFinder(EventList &eventlist, const string &name, ConnectionMatrix *matrix, const Constellation& constellation)
: EventSource(eventlist,name), _matrix(matrix), _constellation(constellation)
{

}
