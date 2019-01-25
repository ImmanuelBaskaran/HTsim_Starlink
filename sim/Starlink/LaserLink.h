//
// Created by metal on 25/01/19.
//

#define SIM_LASERLINK_H


#include <eventlist.h>
#include <pipe.h>



class LaserLink : public Pipe {
public:
    LaserLink(simtime_picosec delay, EventList& eventlist);
    void receivePacket(Packet& pkt); // inherited from Pipe
    void doNextEvent(); // inherited from Pipe
    simtime_picosec delay() { return _delay; }
    const string& nodename() { return _nodename; }
private:
    simtime_picosec _delay;
    typedef pair<simtime_picosec,Packet*> pktrecord_t;
    list<pktrecord_t> _inflight; // the packets in flight (or being serialized)
    string _nodename;
};



