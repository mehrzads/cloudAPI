CC=g++-4.8
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -lpthread -lz -lsnappy
SOURCES= src/server.cpp ../Common/src/compression.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES= -I. -Iinclude/ -I../Common/include       

EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) src/*.o


