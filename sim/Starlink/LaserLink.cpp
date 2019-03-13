#include "LaserLink.h"
#include "StarlinkLib.h"


LaserLink::LaserLink(simtime_picosec delay1, EventList &eventlist1, const Node& node1, const Node& node2,
                     bool isSatelliteLink) : Pipe(delay1, eventlist1), _node1(node1), _node2(node2),
                     _isSatelliteLink(isSatelliteLink) {
    // Do we need to do this in the constructor when we already do it for every doNextEvent()?
    double distance = getNodeDistance(_node1, _node2, _eventlist.now());
    if(checkIsSatellite()){
        Pipe::_delay = timeFromSec(distance / 299792458);
    } else{
        Pipe::_delay = timeFromSec(distance / 3e+8);
    }
    _nodename = "LaserLink";
}

void LaserLink::doNextEvent() {
    double distance = getNodeDistance(_node1, _node2, _eventlist.now());
    if(checkIsSatellite()){
        Pipe::_delay = timeFromSec(distance / 299792458);
    } else{
        Pipe::_delay = timeFromSec(distance / 3e+8);
    }
    
    Pipe::doNextEvent();
}