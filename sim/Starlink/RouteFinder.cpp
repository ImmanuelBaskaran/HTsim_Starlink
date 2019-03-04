#include "Satellite.h"
#include "RouteFinder.h"
#include "ConnectionMatrix.h"
#include "network.h"

#define NUM_SATELLITES 1584

double getDistanceBetweenSatellitePair(const Satellite& satellite1, const Satellite& satellite2){
    Eigen::Vector3d position1 = satellite1.getPosition();
    Eigen::Vector3d  position2 = satellite2.getPosition();
    return (position2 - position1).norm();
}

//construct distances matrix

double** get_dist_sat_conn_matrix(uint8_t** matrix)
{
    double** dist_matrix = nullptr;
    dist_matrix = new double*[NUM_SATELLITES];

    for(int i=0;i<NUM_SATELLITES;i++) {
        dist_matrix[i] = new double[NUM_SATELLITES];
        for (int j = 0; j < NUM_SATELLITES; j++)
            if (matrix[i][j] == 1) {
                Satellite sat_i = Satellite(i, 1);
                Satellite sat_j = Satellite(j, 1);
                dist_matrix[i][j] = getDistanceBetweenSatellitePair(sat_i, sat_j);
            } else
                dist_matrix[i][j]=INFINITY;
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

void dijkstra (uint8_t ** connectionMatrix, Satellite src)
{
/*    ConnectionMatrix* matrix = new ConnectionMatrix();
    connectionMatrix = matrix->get_connection_matrix();
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
    }*/
}