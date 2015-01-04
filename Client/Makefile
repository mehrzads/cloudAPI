CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -lpthread -lz -lsnappy `pkg-config --cflags --libs protobuf` 
SOURCES= $(wildcard src/*.cpp) $(wildcard ../Common/src/*.cpp)  
PB_OBJS = $(shell find ../Common/pb/ -name '*.pb.o')
OBJECTS=$(SOURCES:.cpp=.o)  $(PB_OBJS) 
INCLUDES= -I. -Iinclude/ -I../Common/include/  -I../Common/pb     

EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean: 
	rm -f $(EXECUTABLE) src/*.o ../Common/src/*.o


