//
// Created by metal on 25/01/19.
//


#include <cstdio>
#include <string.h>
#include "ConnectionMatrix.h"

ConnectionMatrix::ConnectionMatrix(void) {
    for (int satellite = 0; satellite < NUM_SATELLITES; satellite++) {

        int ahead_same_orb_plane;
        int behind_same_orb_plane;
        int ahead_diff_orb_plane;
        int behind_diff_orb_plane;

        if (satellite == NUM_SATELLITES - 1)
            ahead_same_orb_plane = 0;
        else
            ahead_same_orb_plane = satellite + 1;

        if (satellite == 0)
            behind_same_orb_plane = SATTELITES_PER_PLANE - 1;
        else
            behind_same_orb_plane = satellite - 1;

        if(satellite < SATTELITES_PER_PLANE)
            ahead_diff_orb_plane = NUM_SATELLITES -1 - SATTELITES_PER_PLANE -1 + satellite;
        else
            ahead_diff_orb_plane = satellite - SATTELITES_PER_PLANE +1;

        if(satellite > NUM_SATELLITES-SATTELITES_PER_PLANE)
            behind_diff_orb_plane = SATTELITES_PER_PLANE -1 - (NUM_SATELLITES - 1 - satellite);
        else
            behind_diff_orb_plane = satellite + SATTELITES_PER_PLANE -1;


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
    for (int i = 0; i < NUM_SATELLITES; i++) {
        for (int j = 0; j < NUM_SATELLITES; j++) {
            fprintf(fp, "%d,", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

}

