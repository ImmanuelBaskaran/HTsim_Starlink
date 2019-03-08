#include <cstdio>
#include <string.h>
#include <stdint.h>
#include "ConnectionMatrix.h"

uint8_t **matrix;

ConnectionMatrix::ConnectionMatrix(){
    matrix = new uint8_t *[1585];
    for(int i=1; i<1585;i++){
        matrix[i] = new uint8_t[1585];
    }
}

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

            if(satellite <= SATELLITES_PER_PLANE){
                if(satellite < 13){
                    behind_diff_orb_plane = (NUM_SATELLITES - 13) + satellite+1;
                }
                else{
                    behind_diff_orb_plane = (NUM_SATELLITES - SATELLITES_PER_PLANE) + (satellite - 13)+1;
                }

            }
        else{

            if(satellite % SATELLITES_PER_PLANE == 0){
                behind_diff_orb_plane = (satellite - (2*SATELLITES_PER_PLANE)) + 1;
            }
            else{
                behind_diff_orb_plane = satellite - (SATELLITES_PER_PLANE - 1);
            }

        }

        if(satellite >= NUM_SATELLITES - SATELLITES_PER_PLANE){
            ahead_diff_orb_plane = SATELLITES_PER_PLANE - (NUM_SATELLITES - satellite)+13;
        }
        else{

            if(satellite % SATELLITES_PER_PLANE == 1){
                ahead_diff_orb_plane = (satellite + (2*SATELLITES_PER_PLANE)) - 1;
            }
            else{
                ahead_diff_orb_plane = satellite + (SATELLITES_PER_PLANE -1);
            }

        }

        //same orbital plane
        //    matrix[satellite][ahead_same_orb_plane] = 1;
        //    matrix[satellite][behind_same_orb_plane] = 1;
        //     matrix[ahead_same_orb_plane][satellite] = 1;
        //    matrix[behind_same_orb_plane][satellite] = 1;

        //different orbital planes
        matrix[satellite][behind_diff_orb_plane] = 1;
        // printf("%i %i\n", satellite, behind_diff_orb_plane);
        //     matrix[satellite][ahead_diff_orb_plane] = 1;
        // matrix[behind_diff_orb_plane][satellite] = 1;
        //    matrix[ahead_diff_orb_plane][satellite] = 1;

    }
    // int i =1;
    // do{
    //     for(int j = 1; j<1585; j++){
    //         if(matrix[i][j] == 1){
    //             printf("%d connects to %d\n", i, j);
    //             i = j;

    //             break;
    //         }
    //     }
    // }while(i != 1);
    return matrix;
}
