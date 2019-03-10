#pragma once
#include "Satellite.h"

class ConnectionMatrix {
public:
    ConnectionMatrix();
    ~ConnectionMatrix();
    bool areSatellitesConnected(const Satellite& satA, const Satellite& satB) const;
private:
    uint8_t ** _matrix;
};
