CC=g++
CFLAGS=-c -Wall -std=c++11 -fpermissive
LDFLAGS= -lpthread 
SOURCES= src/server.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES= -I. -Iinclude/	

EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) $(LDFLAGS)-o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) *.o


