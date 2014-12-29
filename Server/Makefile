CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS= -lpthread -lz
SOURCES= src/server.cpp src/compression.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES= -I. -Iinclude/	

EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) src/*.o


