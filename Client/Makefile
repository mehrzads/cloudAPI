CC=g++
CFLAGS=-c -Wall -std=c++11 -fpermissive
LDFLAGS= -lpthread 
SOURCES= src/client.cpp src/cloud.cpp
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES= -I. -Iinclude/	

EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean: 
	rm -f $(EXECUTABLE) *.o


