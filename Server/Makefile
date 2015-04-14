CC=mpic++.openmpi
CFLAGS=-c -Wall -std=c++11 -O3
LDFLAGS= -L/opt/OpenBLAS/lib -lopenblas  -lpthread -lz  -lsnappy `pkg-config --cflags --libs protobuf` -L../../scalapack-2.0.2/ -lscalapack -lm -L/usr/lib/gcc/x86_64-linux-gnu/4.8/ -lgfortran 
SOURCES= $(wildcard src/*.cpp) $(wildcard ../Common/src/*.cpp) 
PB_OBJS = $(shell find ../Common/pb/ -name '*.pb.o')
OBJECTS=$(SOURCES:.cpp=.o) $(PB_OBJS)
INCLUDES= -I. -Iinclude/ -I../Common/include -I../Common/pb/  -I/opt/OpenBLAS/include

EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)  
	$(CC)  $(OBJECTS)  $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) src/*.o


