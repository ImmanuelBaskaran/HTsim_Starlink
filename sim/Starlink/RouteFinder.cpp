#include "RouteFinder.h"
#include "Constellation.h"

//construct distances matrix

void RouteFinder::updateDistMatrix(simtime_picosec now) {
    for(int i=1;i<=NUM_SATELLITES;i++) {
        // Distance between linked satellites
        for (int j = 1; j <= NUM_SATELLITES; j++) {
            Satellite* sat_i = _constellation.getSatByID(i);
            Satellite* sat_j = _constellation.getSatByID(j);
            if (_connMatrix.areSatellitesConnected(*sat_i, *sat_j)) {
                Eigen::Vector3d position1 = sat_i->getPosition(now);
                Eigen::Vector3d position2 = sat_j->getPosition(now);
                _distMatrix[i][j] = (position2 - position1).norm();
            } else
                _distMatrix[i][j] = INT_MAX;
        }
        // Distance between satellites and ground stations
        for (int j = NUM_SATELLITES + 1; j < DIST_MATRIX_SIZE; j++) {
            Satellite* sat = _constellation.getSatByID(i);
            GroundStation* gst = _constellation.getGroundStation(j);
            if (gst->isSatelliteInRange(*sat, now)) {
                _distMatrix[i][j] = (sat->getPosition(now) - gst->getPosition(now)).norm();
            } else {
                _distMatrix[i][j] = INT_MAX;    
            }
        }
    }
    for (int i = NUM_SATELLITES + 1; i < DIST_MATRIX_SIZE; i++) {
        // Distance between satellites and ground stations
        for (int j = 1; j <= NUM_SATELLITES; j++) {
            Satellite* sat = _constellation.getSatByID(j);
            GroundStation* gst = _constellation.getGroundStation(i);
            if (gst->isSatelliteInRange(*sat, now)) {
                _distMatrix[i][j] = (sat->getPosition(now) - gst->getPosition(now)).norm();
            } else {
                _distMatrix[i][j] = INT_MAX;    
            }
        }
        // Distance between ground stations (infinite)
        for (int j = NUM_SATELLITES + 1; j < DIST_MATRIX_SIZE; j++) {
            _distMatrix[i][j] = INT_MAX;
        }
    }
}

int RouteFinder::minDistance(double dist[], bool sptSet[]) {
    // Initialize min value
    double min = INT_MAX;
    int min_index=INT_MAX;

    for (int v = 1; v < DIST_MATRIX_SIZE; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

std::vector<int> RouteFinder::extractPath(int* parent, int destId) {
    std::vector<int> path;
    int parentId = destId;
    while (parentId != -1) {
        path.push_back(parentId);
        parentId = parent[parentId];
    }
    std::reverse(path.begin(), path.end());
    return path;
}


std::vector<int> RouteFinder::dijkstra (const GroundStation& src, const GroundStation& dest, simtime_picosec now) {
    updateDistMatrix(now);
    // output, will hold the shortest distance from src to i, should to to sink
    double dist[DIST_MATRIX_SIZE];
    // parent[x] = which node (sat / ground station) we passed through to get to x
    int parent[DIST_MATRIX_SIZE];
    // shortest path tree set, keeps track of satellite links included
    bool sptSet[DIST_MATRIX_SIZE];

    for(int i=1;i< DIST_MATRIX_SIZE;i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // `src` has no parent node (-1) and zero cost
    dist[src.getId()] = 0;
    parent[src.getId()] = -1;

    for(int count =1; count<DIST_MATRIX_SIZE-1; count++) {
        int u = minDistance(dist, sptSet); //pick minimum distance link not yet included to sptSet
        sptSet[u] = true;
        for (int v = 1; v < DIST_MATRIX_SIZE; v++) {
            if (!sptSet[v] && _distMatrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + _distMatrix[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + _distMatrix[u][v];
            }
        }
    }
    return extractPath(parent, dest.getId());
}


RouteFinder::RouteFinder(const Constellation& constellation, const ConnectionMatrix& connMatrix)
                        : _constellation(constellation), _connMatrix(connMatrix)
{}
