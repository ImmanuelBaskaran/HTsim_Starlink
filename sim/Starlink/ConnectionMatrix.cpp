
#include <cstdio>
#include <string.h>
#include <stdint.h>
#include "ConnectionMatrix.h"

uint8_t **  ConnectionMatrix::get_connection_matrix()
{
    for (int satellite = 1; satellite <= NUM_SATELLITES; satellite++) {

        int ahead_same_orb_plane;
        int behind_same_orb_plane;
        int ahead_diff_orb_plane;
        int behind_diff_orb_plane;

        if (satellite % SATELLITES_PER_PLANE == 0)
            ahead_same_orb_plane = satellite - (SATELLITES_PER_PLANE - 1);
        else
            ahead_same_orb_plane = satellite + 1;

        if (satellite % SATELLITES_PER_PLANE == 1)
            behind_same_orb_plane = satellite + (SATELLITES_PER_PLANE-1);
        else
            behind_same_orb_plane = satellite - 1;

        if(satellite <= SATELLITES_PER_PLANE)
            ahead_diff_orb_plane = NUM_SATELLITES - SATELLITES_PER_PLANE + satellite-13;
        else
            ahead_diff_orb_plane = satellite - SATELLITES_PER_PLANE ;

        if(satellite >= NUM_SATELLITES - SATELLITES_PER_PLANE)
            behind_diff_orb_plane = SATELLITES_PER_PLANE - (NUM_SATELLITES - satellite)+13;
        else
            behind_diff_orb_plane = satellite + SATELLITES_PER_PLANE ;

         matrix = new uint8_t *[1584];
         for(int i=0; i<1584;i++){
             matrix[i] = new uint8_t;
         }

        //same orbital plane
        matrix[satellite][ahead_same_orb_plane] = 1;
        matrix[satellite][behind_same_orb_plane] = 1;
        matrix[ahead_same_orb_plane][satellite] = 1;
        matrix[behind_same_orb_plane][satellite] = 1;

        //different orbital planes
        matrix[satellite][ahead_diff_orb_plane] = 1;
        matrix[satellite][behind_diff_orb_plane] = 1;
        matrix[ahead_diff_orb_plane][satellite] = 1;
        matrix[behind_diff_orb_plane][satellite] = 1;

    }
    return matrix;
}

