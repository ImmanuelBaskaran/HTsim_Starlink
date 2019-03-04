OBJS=OrbitalPlane.o Satellite.o LaserLink.o GroundStation.o ConnectionMatrix.o
HDRS=OrbitalPlane.h Satellite.h LaserLink.h GroundStation.h ConnectionMatrix.h

CC = g++
CFLAGS = -Wall -g -O
CRT=`pwd`
INCLUDE= -I/$(CRT)/.. -I$(CRT) -g
#EIGEN= -I /home/user/eigen/Eigen
#-I$(CRT)/ksp -I$(CRT)/ksp/boost
LIB=-L.. 
#-Lksp

all:	simple lib
#htsim_ndp_incast_shortflows_demo 

clean:	
	rm -f *.o simple libhtsim.a

simple:	simple.o $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) simple.o $(LIB) -lhtsim -o simple

lib: $(OBJS) $(HDRS)

simple.o: simple.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -c simple.cpp 

OrbitalPlane.o: OrbitalPlane.cpp $(HDRS)
	$(CC) $(INCLUDE) $(CFLAGS) -c OrbitalPlane.cpp 

Satellite.o: Satellite.cpp $(HDRS)
	$(CC) $(INCLUDE) $(CFLAGS) -c Satellite.cpp 

LaserLink.o: LaserLink.cpp $(HDRS)
	$(CC) $(INCLUDE) $(CFLAGS) -c LaserLink.cpp 

GroundStation.o: GroundStation.cpp $(HDRS)
	$(CC) $(INCLUDE) $(CFLAGS) -c GroundStation.cpp 

ConnectionMatrix.o: ConnectionMatrix.cpp $(HDRS)
	$(CC) $(INCLUDE) $(CFLAGS) -c ConnectionMatrix.cpp 




