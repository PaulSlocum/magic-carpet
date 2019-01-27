appname := magic_carpet.prg

CXX := gcc
CXXFLAGS := `sdl2-config --cflags --libs` \
-DPLATFORM_RPI \
-g \
-s \
-Wall \
-Wpedantic \
-Wextra \
-std=c++17 \
-Wno-unknown-pragmas \
-lSDL2 \
-lm \
-lstdc++ \
-Ilib/sdl/include \
-Ilib/ujpeg \
-Ilib/stb_vorbis \
-Wno-variadic-macros 


LDLIBS := -L/opt/vc/lib \
-lbcm_host \
-lvcos \
-lvchostif \
-lvchiq_arm \
-lpthread \
-lasound 

#-lefence 


#############################################################################

srcfiles := source/mc_util.cpp source/mc_main.cpp source/mc_renderer.cpp \
 source/mc_application.cpp lib/ujpeg/ujpeg.cpp source/mc_sprite.cpp \
 source/mc_game.cpp source/mc_input.cpp source/mc_game_screen.cpp \
 source/mc_menu_screen.cpp source/mc_audio.cpp lib/stb_vorbis/stb_vorbis.cpp

objects := source/mc_util.o source/mc_main.o source/mc_renderer.o \
 source/mc_application.o lib/ujpeg/ujpeg.o source/mc_sprite.o \
 source/mc_game.o source/mc_input.cpp source/mc_game_screen.o \
 source/mc_menu_screen.o source/mc_audio.o lib/stb_vorbis/stb_vorbis.o

#############################################################################

#objects	 := $(patsubst %.cpp, %.o, $(srcfiles))



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
