// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// --- Starlink includes
#include "Constellation.h"
#include "LaserLink.h"
// ---

#include "config.h"
#include <sstream>
#include <string.h>
#include <strstream>
#include <iostream>
#include <math.h>
#include "network.h"
#include "randomqueue.h"
#include "pipe.h"
#include "eventlist.h"
#include "logfile.h"
#include "cbr.h"
#include "loggers.h"
#include "clock.h"
#include "mtcp.h"
#include "exoqueue.h"

string ntoa(double n);
string itoa(uint64_t n);

#define CAP 1

// Simulation params
double targetwnd = 30;
int NUMFLOWS = 2;

#define TCP_1 0
#define TCP_2 0

#define RANDOM_BUFFER 3

#define FEEDER_BUFFER 2000

void exit_error(char* progr){
    cout << "Usage " << progr << " [UNCOUPLED(DEFAULT)|COUPLED_INC|FULLY_COUPLED|COUPLED_EPSILON] rate rtt" << endl;
    exit(1);
}

int main(int argc, char **argv) {
    simtime_picosec extrastarttime = timeFromSec(87.4);
    EventList eventlist;
    eventlist.setEndtime(timeFromSec(DEBUG_SIMULATION_END_TIME_IN_SECS));
    Clock c(timeFromSec(50/100.), eventlist);
    int algo = UNCOUPLED;
    double epsilon = 1;
    int crt = 2;


    linkspeed_bps SERVICE1 = speedFromMbps(40.0 * 1024.0);
    linkspeed_bps SERVICE2 = speedFromMbps(40.0 * 1024.0);

    simtime_picosec RTT1=timeFromMs(150);
    simtime_picosec RTT2 = timeFromMs(10);

    // Set queue size to infinite
    mem_b BUFFER1 = INT64_MAX;

    int bufsize = timeAsSec(RTT2)*speedAsPktps(SERVICE2)*4;
    if (bufsize<10)
        bufsize = 10;

    mem_b BUFFER2=memFromPkt(RANDOM_BUFFER+bufsize);

    int rwnd;

    rwnd = 3 * timeAsSec(max(RTT1,RTT2)) * (speedAsPktps(SERVICE1)+speedAsPktps(SERVICE2));

    int run_paths = 2;
    //0 means run 3g only
    //1 means run wifi only

    srand(time(NULL));

    // prepare the loggers
    stringstream filename(ios_base::out);
    filename << "../data/logout." << speedAsPktps(SERVICE2) << "pktps." <<timeAsMs(RTT2) << "ms." << rwnd << "rwnd2.txt"; // rand();
    // cout << "Outputting to " << filename.str() << endl;
    Logfile logfile(filename.str(),eventlist);

    logfile.setStartTime(timeFromSec(0.0));

    QueueLoggerSimple loggerSimple = QueueLoggerSimple();
    logfile.addLogger(loggerSimple);

    simtime_picosec extrastarttime = DEBUG_SIMULATION_START_TIME_IN_PICOSECS;
    Constellation constellation = Constellation(eventlist,"ElonMusk",SERVICE1, BUFFER1,&loggerSimple);

    GroundStation* london = constellation.getGroundStation(NUM_SATELLITES + 1);
    GroundStation* johannesburg = constellation.getGroundStation(NUM_SATELLITES + 2);
    london->setDestination(johannesburg);
    route_t* dummy = new route_t();
    london->connect(*dummy, *johannesburg, extrastarttime);

    // Record the setup
    int pktsize = Packet::data_packet_size();
    logfile.write("# pktsize="+ntoa(pktsize)+" bytes");
    logfile.write("# bottleneckrate1="+ntoa(speedAsPktps(SERVICE1))+" pkt/sec");
    logfile.write("# bottleneckrate2="+ntoa(speedAsPktps(SERVICE2))+" pkt/sec");
    //  logfile.write("# buffer1="+ntoa((double)(testQueue._maxsize)/((double)pktsize))+" pkt");
    //	logfile.write("# buffer2="+ntoa((double)(queue2._maxsize)/((double)pktsize))+" pkt");
    double rtt = timeAsSec(RTT1);
    logfile.write("# rtt="+ntoa(rtt));
    rtt = timeAsSec(RTT2);
    logfile.write("# rtt="+ntoa(rtt));
    logfile.write("# numflows="+ntoa(NUMFLOWS));
    logfile.write("# targetwnd="+ntoa(targetwnd));

    // GO!
    while (eventlist.doNextEvent()) { }


}

string ntoa(double n) {
    stringstream s;
    s << n;
    return s.str();
}
string itoa(uint64_t n) {
    stringstream s;
    s << n;
    return s.str();
}
