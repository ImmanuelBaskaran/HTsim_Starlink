//
// Created by metal on 25/01/19.
//


#include <cstdio>
#include <string.h>
#include "ConnectionMatrix.h"

ConnectionMatrix::ConnectionMatrix(void) {
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
            ahead_diff_orb_plane = NUM_SATELLITES - SATELLITES_PER_PLANE + satellite;
        else
            ahead_diff_orb_plane = satellite - SATELLITES_PER_PLANE ;

        if(satellite >= NUM_SATELLITES - SATELLITES_PER_PLANE)
            behind_diff_orb_plane = SATELLITES_PER_PLANE - (NUM_SATELLITES - satellite);
        else
            behind_diff_orb_plane = satellite + SATELLITES_PER_PLANE ;


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
    FILE *fp;
    fp = fopen("connectionMatrix.csv", "w+");
    for (int i = 1; i <= NUM_SATELLITES; i++) {
        for (int j = 1; j <= NUM_SATELLITES; j++) {
            fprintf(fp, "%d,", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

}

