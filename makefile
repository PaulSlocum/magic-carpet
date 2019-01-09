appname := magic_carpet.prg

CXX := gcc
CXXFLAGS := `sdl2-config --cflags --libs` \
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

#-DVIDEO_PLAYER \
#-L/usr/lib/omxplayer/ \
#-lSDL2_ttf-2.0 \
#-I/opt/vc/include \
#-lbluetooth \
#-lfreeimage \
#-lfreeimageplus \
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

#-lSDL2_image 

#-std=gnu++11 
#-std=c++11 

# WORKS FOR BUILDING FREEIMAGE TEST --> gcc freeimageTest.cpp -o free.prg -lfreeimage -lstdc++ -lfreeimageplus

# THIS WORKS FOR BUILDING TVSERVICE ON STANDALONE GCC --->   -L/opt/vc/lib -lvcos -lbcm_host -lvchostif -lpthread -lvchiq_arm 
# THIS ALSO FOR BUILDING TVSERVICE ON STANDALONE GCC  --->   -L/opt/vc/lib -lvcos -lvchostif -lpthread -lvchiq_arm 

#-lvcos 
#-lopenmaxil 
#-L/opt/vc/lib/libbcm_host.so 
#-L/opt/vc/lib/libvchostif.a 
#-Lopt/vc/lib/libmmal_core.so 
#-Lopt/vc/lib/libvcos.so

#############################################################################

srcfiles := sdl_main.cpp

objects := sdl_main.o 

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
	rm -f *.o
#	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend
