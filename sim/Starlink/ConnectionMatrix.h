

#ifndef SIM_CONNECTIONMATRIX_H
#define SIM_CONNECTIONMATRIX_H


const int NUM_SATELLITES = 1584;
const int ORBITAL_PLANES=24;
const int SATELLITES_PER_PLANE=66;


class ConnectionMatrix {
public:
    ConnectionMatrix(){};  // This is the constructor
    uint8_t ** get_connection_matrix();

private:
    uint8_t ** matrix;
};


#endif //SIM_CONNECTIONMATRIX_H
