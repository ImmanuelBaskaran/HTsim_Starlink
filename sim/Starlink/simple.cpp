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
#include "Constellation.h"

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
int getLinkFromFirstSat(pair<int,int> p,vector<pair<pair<int,int>,LaserLink>> l){
    for(int i = 0;i<l.size();i++){
        // printf("Test %i,%i\n",l[i].first.first,l[i].first.second);
        if(l[i].first.first==p.first){
            // printf("This is going to return satellite %i\n",l[i].first.first);
            return i;
        }
    }

}

int getLinkFromFirst(pair<int,int> p,vector<pair<pair<int,int>,LaserLink>> l){
    // printf("I am looking for Test %i,%i\n",p.first,p.second);
    for(int i = 0;i<l.size();i++){
        //printf("Test %i,%i\n",l[i].first.first,l[i].first.second);
        if(l[i].first.first==p.first && l[i].first.second == p.second){
            // printf("This is going to return satellite %i\n",l[i].first.second);
            return i;
        }
    }

}



int main(int argc, char **argv) {
    EventList eventlist;
    eventlist.setEndtime(timeFromSec(60));
    Clock c(timeFromSec(50/100.), eventlist);
    int algo = UNCOUPLED;
    double epsilon = 1;
    int crt = 2;


    linkspeed_bps SERVICE1 = speedFromPktps(400);
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

    logfile.setStartTime(timeFromSec(0.0));
//
//    QueueLoggerSimple loggerSimple = QueueLoggerSimple();
//    logfile.addLogger(loggerSimple);
//
//    Queue testQueue(SERVICE1, BUFFER1, eventlist,&loggerSimple);
//    testQueue.setName("testQueue");
//    logfile.writeName(testQueue);
//
//    CbrSrc* cbrSource;
//    CbrSink* cbrSink1;
//    route_t* route;
//    Eigen::Vector3f pos1(1,1,1);
//    Eigen::Vector3f pos2(20,20,20);
//
//
//
//    Satellite dummy = Satellite(1,1);
//    Satellite dummy2 = Satellite(1,1);
//
//
//    dummy.setPosition(pos2);
//    dummy2.setPosition(pos1);
//
//    LaserLink* pipe1 = new LaserLink(100000, eventlist,dummy,dummy2);
//    pipe1->setName("pipe1");
//    logfile.writeName(*pipe1);
//
//    cbrSource = new CbrSrc(eventlist,SERVICE1);
//    cbrSink1 = new CbrSink();
//
//
//    Queue linkUp(SERVICE1, BUFFER1, eventlist,&loggerSimple);
//    testQueue.setName("linkUp");
//    logfile.writeName(linkUp);
//
//    Pipe* pipeup = new Pipe(100000, eventlist);
//    pipe1->setName("pipeup");
//    logfile.writeName(*pipeup);
//
//
//    Queue linkDown(SERVICE1, BUFFER1, eventlist,&loggerSimple);
//    testQueue.setName("linkDown");
//    logfile.writeName(linkDown);
//
//    Pipe* pipedown = new Pipe(100000, eventlist);
//    pipe1->setName("pipedown");
//    logfile.writeName(*pipedown);
//
//    route = new route_t();
//
//    route->push_back(&linkUp);
//    route->push_back(pipeup);
//
//    route->push_back(&testQueue);
//    route->push_back(pipe1);
//
//    route->push_back(&linkDown);
//    route->push_back(pipedown);
//
//    route->push_back(((PacketSink*) &station1));
//


    QueueLoggerSimple loggerSimple = QueueLoggerSimple();
    logfile.addLogger(loggerSimple);
    route_t* route;

    GroundStation station1 = GroundStation(eventlist,51.5074, 0.1278);
    GroundStation station2 = GroundStation(eventlist,51.5074,0.1278);

    // double extrastarttime = drand()*50;
    //station2.connect(*route,*cbrSink1,timeFromMs(extrastarttime));

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


    ConnectionMatrix mat = ConnectionMatrix();
    uint8_t ** test = mat.get_connection_matrix();

    Constellation constellation = Constellation(eventlist,"ElonMusk");

    Queue* queues[NUM_SATELLITES];

    for(int i =0;i<NUM_SATELLITES;i++){
        queues[i] = new Queue(SERVICE1, BUFFER1, eventlist,&loggerSimple);
    }

    vector<pair<pair<int,int>,LaserLink>> list;
    for(int i =1;i<NUM_SATELLITES;i++){
        for(int j =1;j<NUM_SATELLITES;j++){
            //   printf("%i ",test[i][j]);
            if(test[i][j]==1){
                //printf("Elon musk says that sat %i connects to sat %i\n",i,j);

                list.push_back(make_pair(make_pair(i,j),LaserLink(0,eventlist,*constellation.getSatByID(i-1),
                                                                  *constellation.getSatByID(j-1))));
            }
        }
        // printf("\n");
    }

    route = new route_t();

    Queue linkUp(SERVICE1, BUFFER1, eventlist, nullptr);
    linkUp.setName("linkUp");
    logfile.writeName(linkUp);

    Pipe* pipeup = new Pipe(100, eventlist);
    pipeup->setName("pipeup");
    logfile.writeName(*pipeup);


    Queue linkDown(SERVICE1, BUFFER1, eventlist, nullptr);
    linkDown.setName("linkDown");
    logfile.writeName(linkDown);

    Pipe* pipedown = new Pipe(100, eventlist);
    pipedown->setName("pipedown");
    logfile.writeName(*pipedown);
    route->push_back(&linkUp);
    route->push_back(pipeup);


    for(int i = 1; i <= 66; i++){
        int currSat = i;
        int nextSat;
            Eigen::Vector3d pos = constellation.getSatByID(currSat-1)->getPosition(0);
            printf("%f %f %f\n" , pos.x(), pos.y(), pos.z());
        //    printf("%d %f %f %f\n",currSat , pos.x(), pos.y(), pos.z());
        for(int j = 1; j<1585; j++){
                if(test[currSat][j] == 1){
                    // printf("%d connects to %d\n", currSat, j);
                    nextSat = j;
                    break;
                }
            }
        do{
            route->push_back(queues[currSat-1]);
            route->push_back(&list[getLinkFromFirst(make_pair(currSat,nextSat),list)].second);
            int currsatTemp = currSat;
            currSat=nextSat;
            for(int j = 1; j<1585; j++){
                if(test[currSat][j] == 1){
                    // printf("%d connects to %d\n", currSat, j);
                    nextSat = j;
                    break;
                }
            }

            Eigen::Vector3d pos = constellation.getSatByID(currSat-1)->getPosition(0);
            printf("%f %f %f\n", pos.x(), pos.y(), pos.z());
        //    printf("%d %f %f %f\n",currSat , pos.x(), pos.y(), pos.z());
        } while (currSat != i);
        printf("\n\n");
    }


    // int currSat = 1;
    // int nextSat;
    //     Eigen::Vector3d pos = constellation.getSatByID(currSat-1)->getPosition();
    //     printf("%f %f %f\n" , pos.x(), pos.y(), pos.z());
    // //    printf("%d %f %f %f\n",currSat , pos.x(), pos.y(), pos.z());
    //    for(int j = 1; j<1585; j++){
    //         if(test[currSat][j] == 1){
    //             // printf("%d connects to %d\n", currSat, j);
    //             nextSat = j;
    //             break;
    //         }
    //     }
    // do{
    //     route->push_back(queues[currSat-1]);
    //     route->push_back(&list[getLinkFromFirst(make_pair(currSat,nextSat),list)].second);
    //     int currsatTemp = currSat;
    //     currSat=nextSat;
    //     for(int j = 1; j<1585; j++){
    //         if(test[currSat][j] == 1){
    //             // printf("%d connects to %d\n", currSat, j);
    //             nextSat = j;
    //             break;
    //         }
    //     }

    //     Eigen::Vector3d pos = constellation.getSatByID(currSat-1)->getPosition();
    //     printf("%f %f %f\n", pos.x(), pos.y(), pos.z());
    // //    printf("%d %f %f %f\n",currSat , pos.x(), pos.y(), pos.z());
    // } while (currSat != 1);


    route->push_back(&linkDown);
    route->push_back(pipedown);
    route->push_back(((PacketSink*) &station1));

    double extrastarttime = drand()*50;
    station2.connect(*route,station1,0);

    // GO!
    while (eventlist.doNextEvent()) {
    }
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
