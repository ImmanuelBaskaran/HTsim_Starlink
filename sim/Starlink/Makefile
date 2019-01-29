OBJS=OrbitalPlane.o Satellite.o ISL.o
HDRS=OrbitalPlane.h Satellite.h ISL.h

CC = g++
CFLAGS = -Wall -g -O
CRT=`pwd`
INCLUDE= -I/$(CRT)/.. -I$(CRT)
EIGEN= -I /home/user/eigen/Eigen
#-I$(CRT)/ksp -I$(CRT)/ksp/boost
LIB=-L.. 
#-Lksp

all:	simple lib
#htsim_ndp_incast_shortflows_demo 

CFLAGS = -I  *.h ../pipe.h

simple:	simple.o
	$(CC) $(CFLAGS) simple.o $(LIB) -lhtsim -o simple

lib: $(OBJS) $(HDRS)

simple.o: simple.cpp
	$(CC) $(INCLUDE) $(EIGEN) $(CFLAGS) -c simple.cpp 

OrbitalPlane.o: OrbitalPlane.cpp $(HDRS)

Satellite.o: Satellite.cpp $(HDRS)

ISL.o: ISL.cpp $(HDRS)

