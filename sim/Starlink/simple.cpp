// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-
#include "OrbitalPlane.h"

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
#include "ConnectionMatrix.h"
#include "LaserLink.h"
#include "GroundStation.h"

string ntoa(double n);
string itoa(uint64_t n);

#define CAP 1

// Simulation params
double targetwnd = 30;
int NUMFLOWS = 2;

#define TCP_1 0
#define TCP_2 0

#define RANDOM_BUFFER 3
#define ALTITUDE 550000

#define FEEDER_BUFFER 2000

void exit_error(char* progr){
    cout << "Usage " << progr << " [UNCOUPLED(DEFAULT)|COUPLED_INC|FULLY_COUPLED|COUPLED_EPSILON] rate rtt" << endl;
    exit(1);
}

double toRadians(double degrees){
    return (degrees * (M_PI/180));
}

int main(int argc, char **argv) {
    EventList eventlist;
    eventlist.setEndtime(timeFromSec(60));
    Clock c(timeFromSec(50/100.), eventlist);
    int algo = UNCOUPLED;
    double epsilon = 1;
    int crt = 2;


    linkspeed_bps SERVICE1 = speedFromPktps(166);
    linkspeed_bps SERVICE2 = speedFromPktps(400);

    simtime_picosec RTT1=timeFromMs(150);
    simtime_picosec RTT2 = timeFromMs(10);

    mem_b BUFFER1=memFromPkt(RANDOM_BUFFER+timeAsSec(RTT1)*speedAsPktps(SERVICE1)*12);//NUMFLOWS * targetwnd);

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
    cout << "Outputting to " << filename.str() << endl;
    Logfile logfile(filename.str(),eventlist);

    logfile.setStartTime(timeFromSec(0.5));

    QueueLoggerSimple loggerSimple = QueueLoggerSimple();
    logfile.addLogger(loggerSimple);

    Queue testQueue(SERVICE1, BUFFER1, eventlist,&loggerSimple);
    testQueue.setName("testQueue");
    logfile.writeName(testQueue);

    CbrSrc* cbrSource;
    CbrSink* cbrSink1;
    route_t* route;
    Eigen::Vector3d pos1(1,1,1);
    Eigen::Vector3d pos2(20,20,20);

    GroundStation station1 = GroundStation(eventlist,51.5074, 0.1278);
    GroundStation station2 = GroundStation(eventlist,37.0902,95.7129);


    Satellite dummy = Satellite(1,1);
    Satellite dummy2 = Satellite(1,1);


    dummy.setPosition(pos2);
    dummy2.setPosition(pos1);

    LaserLink* pipe1 = new LaserLink(100000, eventlist,dummy,dummy2);
    pipe1->setName("pipe1");
    logfile.writeName(*pipe1);

    cbrSource = new CbrSrc(eventlist,SERVICE1);
    cbrSink1 = new CbrSink();


    Queue linkUp(SERVICE1, BUFFER1, eventlist,&loggerSimple);
    testQueue.setName("linkUp");
    logfile.writeName(linkUp);

    Pipe* pipeup = new Pipe(100000, eventlist);
    pipe1->setName("pipeup");
    logfile.writeName(*pipeup);


    Queue linkDown(SERVICE1, BUFFER1, eventlist,&loggerSimple);
    testQueue.setName("linkDown");
    logfile.writeName(linkDown);

    Pipe* pipedown = new Pipe(100000, eventlist);
    pipe1->setName("pipedown");
    logfile.writeName(*pipedown);

    route = new route_t();

    route->push_back(&linkUp);
    route->push_back(pipeup);

    route->push_back(&testQueue);
    route->push_back(pipe1);

    route->push_back(&linkDown);
    route->push_back(pipedown);

    route->push_back(((PacketSink*) &station1));



    double extrastarttime = drand()*50;
    station2.connect(*route,*cbrSink1,timeFromMs(extrastarttime));




    // Record the setup
    int pktsize = Packet::data_packet_size();
    logfile.write("# pktsize="+ntoa(pktsize)+" bytes");
    logfile.write("# bottleneckrate1="+ntoa(speedAsPktps(SERVICE1))+" pkt/sec");
    logfile.write("# bottleneckrate2="+ntoa(speedAsPktps(SERVICE2))+" pkt/sec");
    logfile.write("# buffer1="+ntoa((double)(testQueue._maxsize)/((double)pktsize))+" pkt");
    //	logfile.write("# buffer2="+ntoa((double)(queue2._maxsize)/((double)pktsize))+" pkt");
    double rtt = timeAsSec(RTT1);
    logfile.write("# rtt="+ntoa(rtt));
    rtt = timeAsSec(RTT2);
    logfile.write("# rtt="+ntoa(rtt));
    logfile.write("# numflows="+ntoa(NUMFLOWS));
    logfile.write("# targetwnd="+ntoa(targetwnd));


    int id = 1;
    int count_gs1=0;
    int count_gs2=0;

    Eigen::Vector3d positionMatrix[24][66];
    for(int i=0; i<24;i++){
        for(int j=0;j<66;j++) {
            Eigen::Vector3d pos;
            pos.x()=0;
            pos.y()=0;
            pos.z()=0;
            positionMatrix[i][j] = pos;
        }
    }

    for (int i = 0; i < 24; i++) {
        OrbitalPlane plane(i + 1, toRadians(i * 15.0), toRadians(53.0), ALTITUDE, toRadians(i * 5.5));
        for (int j = 0; j < SATS_PER_PLANE; j++) {
            Vector3d pos = plane.getPosForSat(id++, timeFromSec(0));
                //printf("%f %f %f\n", pos.x(), pos.y(), pos.z());


            if(station1.isSatelliteInRange(pos, ALTITUDE)) {
                printf("iteration %d\n", j);
                count_gs1++;
                printf("%f %f %f \n\n", pos.x(), pos.y(), pos.z());
            }
            if(station2.isSatelliteInRange(pos, ALTITUDE))
            {

                printf("iteration %d\n", j);
                count_gs2++;
                printf("%f %f %f \n\n", pos.x(), pos.y(), pos.z());
            }

            positionMatrix[i][j]=pos;

        }
    }

    std::vector<Eigen::Vector3d> vect= station1.getSatellitesInRange();
    for(Eigen::Vector3d v: vect)
        printf("%f %f %f \n" , v.x(), v.y(), v.z());

    printf("\n\n\n");

    std::vector<Eigen::Vector3d> vect2= station2.getSatellitesInRange();
    for(Eigen::Vector3d v: vect2)
        printf("%f %f %f \n" , v.x(), v.y(), v.z());



    //  double dist = sqrt(pow(6889661.176128-6267388.183644,2.)+
    //                    pow(525408.625993-2880554.437000,2.)+
    //                    pow(395923.798076-567884.223235,2.));

    // printf("This is distance %f \n", dist/1000);
   
    // GO!
     while (eventlist.doNextEvent()) {
     }
     delete pipe1;
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