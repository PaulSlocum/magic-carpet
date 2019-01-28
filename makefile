# MAGIC CARPET MAKEFILE FOR RASPBERRY PI
#===========================================================================

appname := magic_carpet.prg

CXX := gcc

CXXFLAGS := \
-std=c++17 \
`sdl2-config --cflags --libs` \
-DPLATFORM_RPI \
-g \
-Wall \
-Wpedantic \
-Wextra \
-Wno-unknown-pragmas \
-Wno-variadic-macros \
-Ilib/sdl/include \
-Ilib/ujpeg \
-Ilib/stb_vorbis 

# RELEASE VERSION - STRIP ALL SYMBOL INFO
#-s \


LDLIBS := \
-lSDL2 \
-lm \
-lstdc++



# DISPMANX LIBS TO BE USED FOR RPI VSYNC
#-L/opt/vc/lib -lbcm_host -lvcos -lvchostif -lvchiq_arm



#============================================================================

srcfiles := source/mc_util.cpp source/mc_main.cpp source/mc_renderer.cpp \
 source/mc_application.cpp lib/ujpeg/ujpeg.cpp source/mc_sprite.cpp \
 source/mc_game.cpp source/mc_input.cpp source/mc_game_screen.cpp \
 source/mc_menu_screen.cpp source/mc_audio.cpp lib/stb_vorbis/stb_vorbis.cpp

#===========================================================================

objects	 := $(patsubst %.cpp, %.o, $(srcfiles))



all: $(appname)

$(appname): $(objects) 
	$(CXX) $(CXXFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;



clean:
	rm -f $(appname)
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

include .depend
