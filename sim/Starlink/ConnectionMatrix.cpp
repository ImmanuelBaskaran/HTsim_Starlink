//
// Created by metal on 25/01/19.
//

#include <matrix.h>
#include <cstdio>



const int NUMSATELLITES = 1584;


class ConnectionMatrix {
public:
    ConnectionMatrix();  // This is the constructor

private:
    int matrix[NUMSATELLITES][NUMSATELLITES];
};

ConnectionMatrix::ConnectionMatrix() {
    for(int i=0;i<NUMSATELLITES;i++){
            int orbit = (i / 66);
            int satetllite = i % 66;

            int ahead = (i + 1) % 66;
            int behind = (i - 1) % 66;

            matrix[satetllite+(66*orbit)][ahead+(66*orbit)] = 1;
            matrix[satetllite+(66*orbit)][behind+(66*orbit)] = 1;
    }
    for(int i = 0; i < NUMSATELLITES; i++){
        for(int j = 0; j < NUMSATELLITES; j++){
            printf("%d,",matrix[i][j]);
        }
        printf("\n");

    }

}

