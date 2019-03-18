#include <cstdio>
#include <string.h>
#include <stdint.h>
#include "ConnectionMatrix.h"
#include "StarlinkLib.h"

ConnectionMatrix::ConnectionMatrix() {
    _matrix = new uint8_t *[NUM_SATELLITES + 1];
    for (int i = 1; i <= NUM_SATELLITES; i++) {
        _matrix[i] = new uint8_t[NUM_SATELLITES + 1];
    }
    for (int satellite = 1; satellite <= NUM_SATELLITES; satellite++) {
        int ahead_same_orb_plane;
        int behind_diff_orb_plane;

        if (satellite % NUM_SATS_PER_PLANE == 0) {
            ahead_same_orb_plane = satellite - (NUM_SATS_PER_PLANE - 1);
        } else {
            ahead_same_orb_plane = satellite + 1;
        }


        if (satellite <= NUM_SATS_PER_PLANE) {
            if (satellite < 13) {
                behind_diff_orb_plane = (NUM_SATELLITES - 13) + satellite + 1;
            } else {
                behind_diff_orb_plane = (NUM_SATELLITES - NUM_SATS_PER_PLANE) + (satellite - 13) + 1;
            }
        } else {
            if (satellite % NUM_SATS_PER_PLANE == 0) {
                behind_diff_orb_plane = (satellite - (2 * NUM_SATS_PER_PLANE)) + 1;
            } else {
                behind_diff_orb_plane = satellite - (NUM_SATS_PER_PLANE - 1);
            }
        }
  

        _matrix[satellite][ahead_same_orb_plane] = 1;
        _matrix[ahead_same_orb_plane][satellite] = 1;
        _matrix[satellite][behind_diff_orb_plane] = 1;
        _matrix[behind_diff_orb_plane][satellite] = 1;
    }
}

ConnectionMatrix::~ConnectionMatrix() {
    for (int i = 1; i <= NUM_SATELLITES; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

bool ConnectionMatrix::areSatellitesConnected(const Satellite &satA, const Satellite &satB) const {
    return (_matrix[satA.getId()][satB.getId()] == 1);
}
