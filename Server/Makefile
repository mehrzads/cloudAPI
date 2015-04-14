CC=mpic++.openmpi
CFLAGS=-c -Wall -std=c++11 -O3
LDFLAGS= -L/x/mehrzads/company/ParaBricks/build/lib/ -lopencv_core -lopencv_highgui -lopencv_contrib -lOpenCVDemo -L/opt/OpenBLAS/lib -lopenblas  -lpthread -lz  -lsnappy `pkg-config --cflags --libs protobuf` -L../../scalapack-2.0.2/ -lscalapack -lm -L/usr/lib/gcc/x86_64-linux-gnu/4.8/ -lgfortran 
SOURCES= $(wildcard src/*.cpp) $(wildcard ../Common/src/*.cpp) 
PB_OBJS = $(shell find ../Common/pb/ -name '*.pb.o')
OBJECTS=$(SOURCES:.cpp=.o) $(PB_OBJS)
INCLUDES= -I. \
	  -Iinclude/ \
	  -I../Common/include \
	  -I../Common/pb/      \
	  -I/opt/OpenBLAS/include \
	  -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/include \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/contrib/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/core/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/imgproc/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/features2d/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/flann/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/objdetect/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/modules/highgui/include/ \
          -I/x/mehrzads/company/ParaBricks/ParaBricks/opencv-2.4.11/3rdparty/OpenCVDemo/include/


EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)  
	$(CC)  $(OBJECTS)  $(LDFLAGS) -o $@ 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $< -o $@

clean: 
	rm -f $(EXECUTABLE) src/*.o


