

#ifndef SIM_CONNECTIONMATRIX_H
#define SIM_CONNECTIONMATRIX_H


const int NUM_SATELLITES = 1584;
const int ORBITAL_PLANES=24;
const int SATELLITES_PER_PLANE=66;


class ConnectionMatrix {
public:
    ConnectionMatrix();  // This is the constructor
    __uint8_t [1584][1584] get_connection_matrix();

private:
    __uint8_t matrix[NUM_SATELLITES][NUM_SATELLITES];
};


#endif //SIM_CONNECTIONMATRIX_H
