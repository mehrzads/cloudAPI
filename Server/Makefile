CC=g++-4.8
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -lpthread -lz -lsnappy `pkg-config --cflags --libs protobuf`
SOURCES= src/server.cpp ../Common/src/compression.cpp ../Common/src/cloudTransfer.cpp 
PB_OBJS = $(shell find ../Common/pb/ -name '*.pb.o')
OBJECTS=$(SOURCES:.cpp=.o) $(PB_OBJS)
INCLUDES= -I. -Iinclude/ -I../Common/include -I../Common/pb/

EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)  
	$(CC)  $(OBJECTS)  $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) src/*.o


