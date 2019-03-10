#pragma once

class ConnectionMatrix {
public:
    ConnectionMatrix();
    ~ConnectionMatrix();
    uint8_t ** get_connection_matrix();
private:
    uint8_t ** _matrix;
};
