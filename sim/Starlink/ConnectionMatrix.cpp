#include <cstdio>
#include <string.h>
#include <stdint.h>
#include <fstream>
#include "ConnectionMatrix.h"

uint8_t **  ConnectionMatrix::get_connection_matrix()
{
    _matrix = new uint8_t * [NUM_SATELLITES+1];
    for(int i=0; i<=NUM_SATELLITES;i++){
        _matrix[i] = new uint8_t [NUM_SATELLITES+1];
    }

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

        //same orbital plane
        _matrix[satellite][ahead_same_orb_plane] = 1;
        _matrix[satellite][behind_same_orb_plane] = 1;
        _matrix[ahead_same_orb_plane][satellite] = 1;
        _matrix[behind_same_orb_plane][satellite] = 1;

        //different orbital planes
        _matrix[satellite][ahead_diff_orb_plane] = 1;
        _matrix[satellite][behind_diff_orb_plane] = 1;
        _matrix[ahead_diff_orb_plane][satellite] = 1;
        _matrix[behind_diff_orb_plane][satellite] = 1;

    }
    std::ofstream myfile;
    myfile.open ("example.csv");
    for(int i=0; i<=NUM_SATELLITES;i++){
        for(int j=0; j<=NUM_SATELLITES;j++){
            myfile <<  std::to_string(_matrix[i][j]) + ",";
        }
        myfile <<  "\n";
    }
    myfile.close();
    return _matrix;
}

