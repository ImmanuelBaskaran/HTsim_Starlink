

#ifndef SIM_ROUTEFINDER_H
#define SIM_ROUTEFINDER_H


#include <eventlist.h>
#include "ConnectionMatrix.h"

class RouteFinder : public EventSource {

    public:
        RouteFinder(EventList& eventlist, const string& name, ConnectionMatrix* matrix) : EventSource(eventlist,name), _matrix(matrix){};
        virtual void doNextEvent() = 0;
        inline EventList& eventlist() const {return _eventlist;}
    private:
        ConnectionMatrix* _matrix;
};


#endif //SIM_ROUTEFINDER_H
