appname := slp

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
-lasound \
-ldbus-1

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
# Simple makefile for rpi-openmax-demos.
#
#PROGRAMS = rpi-camera-encode rpi-camera-dump-yuv rpi-encode-yuv rpi-camera-playback
#CC       = gcc
#CFLAGS   = -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -DPIC -D_REENTRANT 
#-D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT 
#-ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM \
#		   -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux \
#		   -fPIC -ftree-vectorize -pipe -Wall -Werror -O2 -g
#LDFLAGS  = -L/opt/vc/lib -lopenmaxil -lvcos -lbcm_host -lpthread
#
#all: $(PROGRAMS)
#
#clean:
#	rm -f $(PROGRAMS)
#
#.PHONY: all clean
#############################################################################


#-lm 
#-lefence 
#-I/home/pi/omxplayer/ffmpeg/libavutil/ \
#-I/home/pi/omxplayer/ffmpeg/ \
#-lavformat -lavcodec -lavutil  -lz -lm -lpthread -I'/usr/local/include' -lswresample

#-lavformat -lavcodec -lavutil  -lz -lm -lpthread 
#-lswresample \
#-lavutil \
# -lm -lz \
#-lavcodec \
#-lavformat
# mpTVService.cpp 

srcfiles := source/sdl_main.cpp

objects := bin/sdl_main.o 

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