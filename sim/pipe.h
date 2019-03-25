// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-        
#ifndef PIPE_H
#define PIPE_H

/*
 * A pipe is a dumb device which simply delays all incoming packets
 */

#include <list>
#include <utility>
#include "config.h"
#include "eventlist.h"
#include "network.h"
#include "loggertypes.h"


class Pipe : public EventSource, public PacketSink {
 public:
    Pipe(simtime_picosec delay, EventList& eventlist);
    virtual void receivePacket(Packet& pkt); // inherited from PacketSink
    virtual void doNextEvent(); // inherited from EventSource
    simtime_picosec delay() { return _delay; }
    const string& nodename() { return _nodename; }
 protected:
    simtime_picosec _delay;
    typedef pair<simtime_picosec,Packet*> pktrecord_t;
    string _nodename;
 private:
    list<pktrecord_t> _inflight; // the packets in flight (or being serialized)
};


#endif
