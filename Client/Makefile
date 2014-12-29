CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -lpthread -lz
SOURCES= src/client.cpp src/cloud.cpp src/compression.cpp
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES= -I. -Iinclude/	

EXECUTABLE=client

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean: 
	rm -f $(EXECUTABLE) src/*.o


