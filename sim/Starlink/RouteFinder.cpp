#include "Satellite.h"
#include "RouteFinder.h"
#include "ConnectionMatrix.h"
#include "network.h"
#include "OrbitalPlane.h"

#define NUM_SATELLITES 1584

double RouteFinder::getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2){
    Eigen::Vector3d position1 = satellite1.getPosition(_eventlist.now());
    Eigen::Vector3d  position2 = satellite2.getPosition(_eventlist.now());
    return (position2 - position1).norm();
}

double toRadians(double degrees){
    return (degrees * (M_PI/180));
}

//construct distances matrix

double** RouteFinder::get_dist_sat_conn_matrix(uint8_t** matrix)
{
    double** dist_matrix = nullptr;
    dist_matrix = new double*[NUM_SATELLITES];

    OrbitalPlane planes[24];
    for (int i = 0; i < 24; i++) {
        int satId = 1;
        planes[i] = OrbitalPlane(i + 1, i * toRadians(15), toRadians(53.0), 550000, i * toRadians(5.5));
    }

    for(int i=0;i<NUM_SATELLITES;i++) {
        int iPlaneIndex = i % 24;
        for (int j = 0; j < NUM_SATELLITES; j++) {
            int jPlaneIndex = j % 24;
            dist_matrix[i] = new double[NUM_SATELLITES];
            if (matrix[i][j] == 1) {
                Satellite* sat_i = planes[iPlaneIndex].getSatByID(i);
                Satellite* sat_j = planes[jPlaneIndex].getSatByID(j);
                dist_matrix[i][j] = getDistanceBetweenSatellitePair(*sat_i, *sat_j);
            } else
                dist_matrix[i][j]=INFINITY;
        }
    }
    return dist_matrix;
}

int minDistance(double dist[], bool sptSet[])
{
    // Initialize min value
    double min = INFINITY;
    int min_index=INFINITY;

    for (int v = 0; v < NUM_SATELLITES; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

bool* RouteFinder::dijkstra (uint8_t ** connectionMatrix, Satellite src)
{
    double** dist_matrix = get_dist_sat_conn_matrix(connectionMatrix);

    double dist[NUM_SATELLITES];   //output, will hold the shortest distance from src to i, should to to sink
    bool sptSet[NUM_SATELLITES];    //shortest path tree set, keeps track of satellite links included

    for(int i=0;i< NUM_SATELLITES;i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src.getID()] = 0;

    for(int count =0; count<NUM_SATELLITES-1; count++) {
        int u = minDistance(dist, sptSet); //pick minimum distance link not yet included to sptSet
        sptSet[u] = true;
        for (int v = 0; v < NUM_SATELLITES; v++) {
            if (!sptSet[v] && dist_matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + dist_matrix[u][v] < dist[v])
                dist[v] = dist[u] + dist_matrix[u][v];
        }
    }
    return sptSet;
}


RouteFinder::RouteFinder(EventList &eventlist, const string &name, ConnectionMatrix *matrix): EventSource(eventlist,name), _matrix(matrix)
{

}
