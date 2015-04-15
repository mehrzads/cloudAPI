CC=g++
CFLAGS=  -c -Wall -std=c++11 -O3
LDFLAGS= -L/x/mehrzads/company/ParaBricks/build/lib/ -lopencv_core -lopencv_highgui -lopencv_contrib -lOpenCVDemo -lpthread -lz -lsnappy `pkg-config --cflags --libs protobuf`  
EXAMPLES= $(wildcard *.cpp)
SOURCES= $(EXAMPLES) $(wildcard ../../src/*.cpp) $(wildcard ../../../Common/src/*.cpp)  
PB_OBJS = $(shell find ../../../Common/pb/ -name '*.pb.o')
OBJECTS=$(SOURCES:.cpp=.o)  $(PB_OBJS) 
INCLUDES= -I.  \
	  -I../../include/ \
	  -I../../../Common/include/  \
	  -I../../../Common/pb     \
	  -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/include \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/contrib/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/core/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/imgproc/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/features2d/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/flann/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/objdetect/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/highgui/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/3rdparty/OpenCVDemo/include/

EXECUTABLE=$(patsubst %.cpp,%,$(EXAMPLES))

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean: 
	rm -f $(EXECUTABLE) ../../src/*.o  ../../../Common/src/*.o


