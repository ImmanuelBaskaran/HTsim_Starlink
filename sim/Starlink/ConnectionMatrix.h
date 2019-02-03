//
// Created by metal on 29/01/19.
//

#ifndef SIM_CONNECTIONMATRIX_H
#define SIM_CONNECTIONMATRIX_H


const int NUM_SATELLITES = 1584;
const int ORBITAL_PLANES=24;
const int SATTELITES_PER_PLANE=66;


class ConnectionMatrix {
public:
    ConnectionMatrix();  // This is the constructor

private:
    __uint8_t matrix[NUMSATELLITES][NUMSATELLITES];
};


#endif //SIM_CONNECTIONMATRIX_H
