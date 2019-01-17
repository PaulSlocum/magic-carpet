appname := magic_carpet.prg

CXX := gcc
CXXFLAGS := `sdl2-config --cflags --libs` \
-DPLATFORM_RPI \
-s \
-Wall \
-Wpedantic \
-Wextra \
-std=c++11 \
-Wno-unknown-pragmas \
-lSDL2 \
-lm \
-lstdc++ \
-I./lib/sdl/include \
-Wno-variadic-macros 

#-lfreeimageplus \
#-lfreeimage \
#-DVIDEO_PLAYER \
#-L/usr/lib/omxplayer/ \
#-lSDL2_ttf-2.0 \
#-I/opt/vc/include \
#-lbluetooth \
#-I/usr/include/dbus-1.0 \
#-I/usr/lib/arm-linux-gnueabihf/dbus-1.0/include 


LDLIBS := -L/opt/vc/lib \
-lbcm_host \
-lvcos \
-lvchostif \
-lvchiq_arm \
-lpthread \
-lasound 

#-ldbus-1

#-lefence 


#-L/opt/vc/lib/libbcm_host.so

# WORKS FOR BUILDING FREEIMAGE TEST --> gcc freeimageTest.cpp -o free.prg -lfreeimage -lstdc++ -lfreeimageplus

#############################################################################

srcfiles := source/mc_util.cpp source/mc_main.cpp source/mc_renderer.cpp\
 source/mc_application.cpp source/ujpeg.cpp

objects := source/mc_util.o source/mc_main.o source/mc_renderer.o\
 source/mc_application.o source/ujpeg.o

#############################################################################

#objects	 := $(patsubst %.cpp, %.o, $(srcfiles))

#srcfiles



all: $(appname)

$(appname): $(objects) 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;



clean:
	rm -f source/*.o
	rm -f $(appname)
#	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend
