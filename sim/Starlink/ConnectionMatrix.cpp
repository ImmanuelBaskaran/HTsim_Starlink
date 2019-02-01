//
// Created by metal on 25/01/19.
//


#include <cstdio>
#include <string.h>
#include "ConnectionMatrix.h"

ConnectionMatrix::ConnectionMatrix(void) {
    for(int i=0;i<NUMSATELLITES;i++){

            int orbit = (i / 66);
            int satetllite = i % 66;

            int ahead = (i + 1) % 66;
            int behind = (i - 1) % 66;
            if(i==0){
                behind = 65;
            }

            matrix[satetllite+(66*orbit)][ahead+(66*orbit)] = 1;
            matrix[satetllite+(66*orbit)][behind+(66*orbit)] = 1;

            matrix[satetllite+(66*orbit)][ahead+(66*orbit)] = 1;
            matrix[satetllite+(66*orbit)][behind+(66*orbit)] = 1;

    }
    FILE *fp;
    fp=fopen("connectionMatrix.csv","w+");
    for(int i = 0; i < NUMSATELLITES; i++){
        for(int j = 0; j < NUMSATELLITES; j++){
            fprintf(fp,"%d,",matrix[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);

}

