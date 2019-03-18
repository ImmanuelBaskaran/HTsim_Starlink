#include "RouteFinder.h"
#include "Constellation.h"
#include "StarlinkLib.h"
#include "float.h"

//construct distances matrix

void RouteFinder::updateDistMatrix(simtime_picosec now) {
    for(int i=1;i<=NUM_SATELLITES;i++) {
        // Distance between linked satellites
        for (int j = 1; j <= NUM_SATELLITES; j++) {
            Satellite* sat_i = _constellation.getSatByID(i);
            Satellite* sat_j = _constellation.getSatByID(j);
            if (_connMatrix.areSatellitesConnected(*sat_i, *sat_j)) {
                _distMatrix[i][j] = getNodeDistance(*sat_i, *sat_j, now);
            } else
                _distMatrix[i][j] = DBL_MAX;
        }
        // Distance between satellites and ground stations
        for (int j = NUM_SATELLITES + 1; j < DIST_MATRIX_SIZE; j++) {
            Satellite* sat = _constellation.getSatByID(i);
            GroundStation* gst = _constellation.getGroundStation(j);
            if (gst->isSatelliteInRange(*sat, now)) {
                _distMatrix[i][j] = getNodeDistance(*gst, *sat, now);
            } else {
                _distMatrix[i][j] = DBL_MAX;    
            }
        }
    }
    for (int i = NUM_SATELLITES + 1; i < DIST_MATRIX_SIZE; i++) {
        // Distance between satellites and ground stations
        for (int j = 1; j <= NUM_SATELLITES; j++) {
            Satellite* sat = _constellation.getSatByID(j);
            GroundStation* gst = _constellation.getGroundStation(i);
            if (gst->isSatelliteInRange(*sat, now)) {
                // printf("Sat. %d is in range of Gst %d\n", j, i);
                _distMatrix[i][j] = getNodeDistance(*gst, *sat, now);
            } else {
                _distMatrix[i][j] = DBL_MAX;    
            }
        }
        // Distance between ground stations (infinite)
        for (int j = NUM_SATELLITES + 1; j < DIST_MATRIX_SIZE; j++) {
            _distMatrix[i][j] = DBL_MAX;
        }
    }
}

int RouteFinder::minDistance(double dist[], bool sptSet[]) {
    // Initialize min value
    double min = DBL_MAX;
    int min_index = INT_MAX;

    for (int v = 1; v < DIST_MATRIX_SIZE; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

std::vector<int> RouteFinder::extractPath(int parent[], int destId) {
    std::vector<int> path;
    int parentId = destId;
    while (parentId != -1) {
        path.push_back(parentId);
        parentId = parent[parentId];
    }
    assert(path.size() > 1);
    // Remove src from path list (not needed in final route_t object)
    path.pop_back();
    std::reverse(path.begin(), path.end());
    return path;
}


route_t* RouteFinder::dijkstra (const GroundStation& src, const GroundStation& dest, simtime_picosec now) {
    updateDistMatrix(now);
    // output, will hold the shortest distance from src to i, should to to sink
    double dist[DIST_MATRIX_SIZE];
    // parent[x] = which node (sat / ground station) we passed through to get to x
    int parent[DIST_MATRIX_SIZE];
    // shortest path tree set, keeps track of satellite links included
    bool sptSet[DIST_MATRIX_SIZE];

    for(int i = 1; i < DIST_MATRIX_SIZE; i++) {
        dist[i] = DBL_MAX;
        parent[i] = -1;
        sptSet[i] = false;
    }

    dist[src.getId()] = 0;

    for(int count = 1; count < DIST_MATRIX_SIZE; count++) {
        int u = minDistance(dist, sptSet); //pick minimum distance link not yet included to sptSet
        sptSet[u] = true;
        if (dist[u] == DBL_MAX) {
            // Min distance is infinite -- nothing more to do
            // printf("Node %d is unreachable from node %d, stopping Dijkstra...\n", u, src.getId());
            break;
        }
        for (int v = 1; v < DIST_MATRIX_SIZE; v++) {
            if (_distMatrix[u][v] == DBL_MAX) {
                // Unreachable node
                continue;
            }

            if (!sptSet[v] && dist[u] + _distMatrix[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + _distMatrix[u][v];
            }
        }
    }
    std::vector<int> path = extractPath(parent, dest.getId());

    route_t* routeToDest = new route_t();

    Satellite* firstSat = _constellation.getSatByID(path[0]);
    LaserLink* firstLink = _constellation.getConnectingLink(src, *firstSat);
    routeToDest->push_back(firstLink);

    for (size_t i = 0; i < path.size() - 1; i++) {
        Node* a = _constellation.getNodeById(path[i]);
        Node* b = _constellation.getNodeById(path[i + 1]);
        LaserLink* link = _constellation.getConnectingLink(*a, *b);

        routeToDest->push_back(a->getPacketSink());
        routeToDest->push_back(link);
    }
    GroundStation* last = _constellation.getGroundStation(path[path.size() - 1]);
    routeToDest->push_back(last);

    // EXPERIMENT DEBUG: Print route between Ground Stations
    // NOTE: Can loop through either `path` (for node IDs) or `routeToDest`
    // to print satellite positions for graphing
    // print_route(*routeToDest);
    return routeToDest;
}


RouteFinder::RouteFinder(const Constellation& constellation, const ConnectionMatrix& connMatrix)
                        : _constellation(constellation), _connMatrix(connMatrix)
{}
