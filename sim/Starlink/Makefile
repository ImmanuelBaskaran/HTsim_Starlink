CC = g++
CFLAGS = -Wall -g -O
CRT=`pwd`
INCLUDE= -I/$(CRT)/.. -I$(CRT) 
#-I$(CRT)/ksp -I$(CRT)/ksp/boost
LIB=-L.. 
#-Lksp

all:	simple
#htsim_ndp_incast_shortflows_demo 

simple:	simple.o
	$(CC) $(CFLAGS) simple.o $(LIB) -lhtsim -o simple


simple.o: simple.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -c simple.cpp 

